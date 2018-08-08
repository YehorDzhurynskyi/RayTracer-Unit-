/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "logger.h"
#include "gui.h"
#include "ft.h"
#include <assert.h>
#include "scenerepo.h"
#include "renderer.h"
#include "window.h"
#include "validation/validation.h"

t_scene						g_main_scene;

static t_scene_meta		scene_meta(void)
{
	t_scene_meta	meta;

	meta.nshapes = 0;
	meta.shapes_size = 0;
	meta.nlightsources = 0;
	meta.lightsources_size = 0;
	meta.nmaterials = 0;
	meta.materials_size = 0;
	meta.ntextures = 0;
	meta.textures_size = 0;
	return (meta);
}

static t_scene_config	scene_config(void)
{
	t_scene_config config;

	config.trace_depth = 20;
	config.aa = NOAA;
	config.global_illumination_enabled = FALSE;
	config.ambient = 0.15;
	config.fov = 60.0;
	config.selected_shape_addr = NONE_SELECTED_ADDR;
	return (config);
}

static void					scene_init_device_buffers(t_scene *scene)
{
	int	err;

	scene->device_shapebuffer = clCreateBuffer(g_clcontext.context, CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY
	| CL_MEM_ALLOC_HOST_PTR, SHAPEBUFF_CAPACITY, NULL, &err);
	if (scene->device_shapebuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	scene->device_lightsourcebuffer = clCreateBuffer(g_clcontext.context, CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY
	| CL_MEM_ALLOC_HOST_PTR, LIGHTSOURCEBUFF_CAPACITY, NULL, &err);
	if (scene->device_lightsourcebuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	scene->device_materialbuffer = clCreateBuffer(g_clcontext.context, CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY
	| CL_MEM_ALLOC_HOST_PTR, MATERIALBUFF_CAPACITY, NULL, &err);
	if (scene->device_materialbuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	scene->device_texturebuffer = clCreateBuffer(g_clcontext.context, CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY
	| CL_MEM_ALLOC_HOST_PTR, TEXTUREBUFF_CAPACITY, NULL, &err);
	if (scene->device_materialbuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
}

void						scene_init_memory(void)
{
	scene_init_device_buffers(&g_main_scene);
	g_main_scene.host_shapebuffer = malloc(SHAPEBUFF_CAPACITY);
	if (g_main_scene.host_shapebuffer == NULL)
		log_fatal("Failed to allocate memory for shape buffer", RT_MEM_ALLOC_ERROR);
	g_main_scene.host_lightsourcebuffer = malloc(LIGHTSOURCEBUFF_CAPACITY);
	if (g_main_scene.host_lightsourcebuffer == NULL)
		log_fatal("Failed to allocate memory for lightsource buffer", RT_MEM_ALLOC_ERROR);
	g_main_scene.host_materialbuffer = malloc(MATERIALBUFF_CAPACITY);
	if (g_main_scene.host_materialbuffer == NULL)
		log_fatal("Failed to allocate memory for material buffer", RT_MEM_ALLOC_ERROR);
	g_main_scene.host_texturebuffer = malloc(TEXTUREBUFF_CAPACITY);
	if (g_main_scene.host_texturebuffer == NULL)
		log_fatal("Failed to allocate memory for texture buffer", RT_MEM_ALLOC_ERROR);
	scene_rewind(&g_main_scene);
}

void						scene_rewind(t_scene *scene)
{
	scene->config = scene_config();
	scene->meta = scene_meta();
	scene->mapped_device_buffer = NULL;
	scene->mapped_host_buffer = NULL;
	clReleaseMemObject(scene->skybox);
	clReleaseMemObject(scene->textures);
	texture_map_cleanup(&scene->texture_map);
}

static inline t_err_code	map_err_code(int err)
{
	if (err == CSON_MEM_ALLOC_ERROR)
		return (RT_MEM_ALLOC_ERROR);
	else if (err == CSON_FILE_OPENING_ERROR)
		return (RT_FILE_OPENING_ERROR);
	else if (err == CSON_FILE_READING_ERROR)
		return (RT_FILE_READING_ERROR);
	else if (err == CSON_KEY_PARSING_ERROR)
		return (RT_KEY_PARSING_ERROR);	
	else if (err == CSON_VALUE_PARSING_ERROR)
		return (RT_VALUE_PARSING_ERROR);
	else if (err == CSON_BRACKETS_PARSING_ERROR)
		return (RT_BRACKETS_PARSING_ERROR);
	else if (err == CSON_EMPTY_DATA_PARSING_ERROR)
		return (RT_EMPTY_DATA_PARSING_ERROR);
	else if (err == CSON_NULL_PARAMETER_ERROR)
		return (RT_NULL_PARAMETER_ERROR);
	return (RT_UNDEFINED_ERROR);
}

void						scene_change(const char *scene_name)
{
	t_cson		*scene_cson;
	char		path[2048];
	t_err_code	err;

	g_should_redraw_scene = FALSE;
	gui_loading_start("Validating scene...");
	ft_strncpy(path, SCENE_DIR, 2048);
	ft_strlcat(path, scene_name, 2048);
	scene_cson = cson_parse_file(path, &err);
	if (err != 0)
	{
		log_error("CSON parsing error", map_err_code(err));
		gui_loading_stop();
		return ;
	}
	err = validate_scene(scene_cson);
	if (err != RT_NO_ERROR)
		log_error("Failed to load scene", RT_RESOURCE_LOADING_ERROR);
	else
	{
		gui_select_object(NONE_SELECTED_ADDR, NONE_TARGET);
		gui_loading_start("Loading scene...");
		load_scene(&g_main_scene, scene_cson);
		log_notify("Scene was loaded successfully");
		g_should_redraw_scene = TRUE;
	}
	cson_free(scene_cson);
	gui_loading_stop();
}

void						scene_cleanup(void)
{
	scene_rewind(&g_main_scene);
	clReleaseMemObject(g_main_scene.device_shapebuffer);
	clReleaseMemObject(g_main_scene.device_lightsourcebuffer);
	clReleaseMemObject(g_main_scene.device_materialbuffer);
	free(g_main_scene.host_shapebuffer);
	free(g_main_scene.host_lightsourcebuffer);
	free(g_main_scene.host_materialbuffer);
}

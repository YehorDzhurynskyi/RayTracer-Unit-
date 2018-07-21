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
#include "ft.h"
#include <assert.h>
#include "scenerepository.h"
#include "renderer.h"

t_scene						g_main_scene;

static t_scenebuffer_meta	scene_meta(void)
{
	t_scenebuffer_meta	meta;

	meta.nshapes = 0;
	meta.shapes_size = 0;
	meta.nlightsources = 0;
	meta.lightsources_size = 0;
	meta.nmaterials = 0;
	meta.materials_size = 0;
	return (meta);
}

static t_scene_config		scene_config(void)
{
	t_scene_config config;

	config.trace_depth = 20;
	config.aa = NOAA;
	config.global_illumination = FALSE;
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
	scene_rewind();
	g_main_scene.mapped_device_buffer = NULL;
	g_main_scene.mapped_host_buffer = NULL;
}

void						scene_rewind(void)
{
	g_main_scene.config = scene_config();
	g_main_scene.meta = scene_meta();
	// g_main_scene.mapped_device_buffer = NULL;
	// g_main_scene.mapped_host_buffer = NULL;
}

void						scene_change(const char *scene_name)
{ //TODO: fixme
	scene_rewind();
	scene_load(&g_main_scene, scene_name);
	log_notify("Scene was switched successfully");
	g_should_redraw_scene = TRUE;
}

void						scene_cleanup(void)
{
	clReleaseMemObject(g_main_scene.device_shapebuffer);
	clReleaseMemObject(g_main_scene.device_lightsourcebuffer);
	clReleaseMemObject(g_main_scene.device_materialbuffer);
	free(g_main_scene.host_shapebuffer);
	free(g_main_scene.host_lightsourcebuffer);
	free(g_main_scene.host_materialbuffer);
}

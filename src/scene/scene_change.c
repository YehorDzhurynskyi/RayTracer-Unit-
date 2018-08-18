/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "scenerepo.h"
#include "renderer.h"
#include "gui.h"
#include "validation/validation.h"

void						scene_rewind(t_scene *scene)
{
	scene->config.trace_depth = 5;
	scene->config.aa = NOAA;
	scene->config.ambient = 0.15;
	scene->config.fov = 60.0;
	scene->config.selected_shape_addr = NONE_SELECTED_ADDR;
	scene->config.cartoon_vfx_enabled = FALSE;
	scene->meta.nshapes = 0;
	scene->meta.shapes_size = 0;
	scene->meta.nlightsources = 0;
	scene->meta.lightsources_size = 0;
	scene->meta.nmaterials = 0;
	scene->meta.materials_size = 0;
	scene->meta.ntextures = 0;
	scene->meta.textures_size = 0;
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

static void					load_new_scene(const t_cson *scene_cson)
{
	gui_select_object(NONE_SELECTED_ADDR, NONE_TARGET);
	gui_loading_start("Loading scene...");
	load_scene(&g_main_scene, scene_cson);
	log_notify("Scene was loaded successfully");
	g_should_redraw_scene = TRUE;
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
		load_new_scene(scene_cson);
	cson_free(scene_cson);
	gui_loading_stop();
}

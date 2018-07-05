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
	config.selected_shape_addr = -1;
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

t_scene						scene_create(void)
{
	t_scene	scene;

	scene_init_device_buffers(&scene);
	scene.host_shapebuffer = malloc(SHAPEBUFF_CAPACITY);
	if (scene.host_shapebuffer == NULL)
		log_fatal("Failed to allocate memory for shape buffer", RT_MEM_ALLOC_ERROR);
	scene.host_lightsourcebuffer = malloc(LIGHTSOURCEBUFF_CAPACITY);
	if (scene.host_lightsourcebuffer == NULL)
		log_fatal("Failed to allocate memory for lightsource buffer", RT_MEM_ALLOC_ERROR);
	scene.host_materialbuffer = malloc(MATERIALBUFF_CAPACITY);
	if (scene.host_materialbuffer == NULL)
		log_fatal("Failed to allocate memory for material buffer", RT_MEM_ALLOC_ERROR);
	scene.config = scene_config();
	scene.meta = scene_meta();
	scene.mapped_device_buffer = NULL;
	scene.mapped_host_buffer = NULL;
	return (scene);
}

void						scene_cleanup(t_scene *scene)
{
	clReleaseMemObject(scene->device_shapebuffer);
	clReleaseMemObject(scene->device_lightsourcebuffer);
	clReleaseMemObject(scene->device_materialbuffer);
	// TODO: this is scene that is mapped on host
	// for faster CPU access
	free(scene->host_shapebuffer);
	free(scene->host_lightsourcebuffer);
	free(scene->host_materialbuffer);
}

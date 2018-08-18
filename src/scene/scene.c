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
#include <assert.h>
#include "window.h"

t_scene		g_main_scene;

#define MEM	CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR

static void	scene_init_device_buffers(t_scene *scene)
{
	int	err;

	scene->device_shapebuffer = clCreateBuffer(g_clcontext.context,
	MEM, SHAPEBUFF_CAPACITY, NULL, &err);
	if (scene->device_shapebuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	scene->device_lightsourcebuffer = clCreateBuffer(g_clcontext.context,
	MEM, LIGHTSOURCEBUFF_CAPACITY, NULL, &err);
	if (scene->device_lightsourcebuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	scene->device_materialbuffer = clCreateBuffer(g_clcontext.context,
	MEM, MATERIALBUFF_CAPACITY, NULL, &err);
	if (scene->device_materialbuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	scene->device_texturebuffer = clCreateBuffer(g_clcontext.context,
	MEM, TEXTUREBUFF_CAPACITY, NULL, &err);
	if (scene->device_materialbuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
}

void		scene_init_memory(void)
{
	scene_init_device_buffers(&g_main_scene);
	g_main_scene.host_shapebuffer = malloc(SHAPEBUFF_CAPACITY);
	if (g_main_scene.host_shapebuffer == NULL)
		log_fatal("Failed to allocate memory for shape buffer",
		RT_MEM_ALLOC_ERROR);
	g_main_scene.host_lightsourcebuffer = malloc(LIGHTSOURCEBUFF_CAPACITY);
	if (g_main_scene.host_lightsourcebuffer == NULL)
		log_fatal("Failed to allocate memory for lightsource buffer",
		RT_MEM_ALLOC_ERROR);
	g_main_scene.host_materialbuffer = malloc(MATERIALBUFF_CAPACITY);
	if (g_main_scene.host_materialbuffer == NULL)
		log_fatal("Failed to allocate memory for material buffer",
		RT_MEM_ALLOC_ERROR);
	g_main_scene.host_texturebuffer = malloc(TEXTUREBUFF_CAPACITY);
	if (g_main_scene.host_texturebuffer == NULL)
		log_fatal("Failed to allocate memory for texture buffer",
		RT_MEM_ALLOC_ERROR);
	scene_rewind(&g_main_scene);
}

void		scene_cleanup(void)
{
	scene_rewind(&g_main_scene);
	clReleaseMemObject(g_main_scene.device_shapebuffer);
	clReleaseMemObject(g_main_scene.device_lightsourcebuffer);
	clReleaseMemObject(g_main_scene.device_materialbuffer);
	free(g_main_scene.host_shapebuffer);
	free(g_main_scene.host_lightsourcebuffer);
	free(g_main_scene.host_materialbuffer);
}

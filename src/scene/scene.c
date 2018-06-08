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

static void	*g_host_shapebuffer;
static void	*g_host_lightbuffer;

t_scene	scene_create(void)
{
	t_scene	scene;
	int		err;

	scene.shapebuffer = clCreateBuffer(g_clcontext.context, CL_MEM_WRITE_ONLY
	| CL_MEM_ALLOC_HOST_PTR, SHAPEBUFFER_CAPACITY, NULL, &err);
	if (scene.shapebuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	scene.shapebuffer_size = 0;
	scene.nshapes = 0;
	g_host_shapebuffer = malloc(SHAPEBUFFER_CAPACITY);
	if (!g_host_shapebuffer)
		log_fatal("Failed to allocate memory for shape buffer", RT_MEM_ALLOC_ERROR);
	scene.host_shapebuffer = g_host_shapebuffer;

	scene.lightbuffer = clCreateBuffer(g_clcontext.context, CL_MEM_WRITE_ONLY
	| CL_MEM_ALLOC_HOST_PTR, LIGHTBUFFER_CAPACITY, NULL, &err);
	if (scene.lightbuffer == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	scene.lightbuffer_size = 0;
	scene.nlights = 0;
	g_host_lightbuffer = malloc(LIGHTBUFFER_CAPACITY);
	if (!g_host_lightbuffer)
		log_fatal("Failed to allocate memory for light buffer", RT_MEM_ALLOC_ERROR);
	scene.host_lightbuffer = g_host_lightbuffer;
	return (scene);
}

void	scene_cleanup(t_scene *scene)
{
	clReleaseMemObject(scene->shapebuffer);
	free(g_host_shapebuffer);
	scene->host_shapebuffer = NULL;
	scene->shapebuffer_size = 0;
	scene->nshapes = 0;
	clReleaseMemObject(scene->lightbuffer);
	free(g_host_lightbuffer);
	scene->host_lightbuffer = NULL;
	scene->lightbuffer_size = 0;
	scene->nlights = 0;
}

void	scene_unmap(t_scene *scene, t_buffer_target target)
{
	int	err;

	assert(target == SHAPE_BUFFER_TARGET || target == LIGHT_BUFFER_TARGET);
	if (target == SHAPE_BUFFER_TARGET)
	{
		err = clEnqueueUnmapMemObject(g_clcontext.command_queue, scene->shapebuffer, scene->host_shapebuffer, 0, NULL, NULL);
		if (err != CL_SUCCESS)
			log_error(opencl_get_error(err), RT_OPENCL_ERROR);
		scene->host_shapebuffer = g_host_shapebuffer;
	}
	else if (target == LIGHT_BUFFER_TARGET)
	{
		err = clEnqueueUnmapMemObject(g_clcontext.command_queue, scene->lightbuffer, scene->host_lightbuffer, 0, NULL, NULL);
		if (err != CL_SUCCESS)
			log_error(opencl_get_error(err), RT_OPENCL_ERROR);
		scene->host_lightbuffer = g_host_lightbuffer;
	}
}

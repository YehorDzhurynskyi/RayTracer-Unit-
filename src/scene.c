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
#include "error.h"
#include "ft.h"

#define SHAPEBUFFER_CAPACITY	4096
#define LIGHTBUFFER_CAPACITY	1024

t_scene	scene_create(void)
{
	t_scene	scene;
	int		err;

	scene.shapebuffer = clCreateBuffer(g_clcontext.context, CL_MEM_WRITE_ONLY
	| CL_MEM_ALLOC_HOST_PTR, SHAPEBUFFER_CAPACITY, NULL, &err);
	if (scene.shapebuffer == NULL || err != CL_SUCCESS)
		print_opencl_error("Failed to create shapebuffer...", err);
	scene.host_shapebuffer = NULL;
	scene.shapebuffer_size = 0;
	scene.nshapes = 0;

	scene.lightbuffer = clCreateBuffer(g_clcontext.context, CL_MEM_WRITE_ONLY
	| CL_MEM_ALLOC_HOST_PTR, LIGHTBUFFER_CAPACITY, NULL, &err);
	if (scene.lightbuffer == NULL || err != CL_SUCCESS)
		print_opencl_error("Failed to create lightbuffer...", err);
	scene.host_lightbuffer = NULL;
	scene.lightbuffer_size = 0;
	scene.nlights = 0;
	return (scene);
}

void	scene_cleanup(t_scene *scene)
{
	clReleaseMemObject(scene->shapebuffer);
	scene->host_shapebuffer = NULL;
	scene->shapebuffer_size = 0;
	scene->nshapes = 0;
	clReleaseMemObject(scene->lightbuffer);
	scene->host_lightbuffer = NULL;
	scene->lightbuffer_size = 0;
	scene->nlights = 0;
}

void	scene_unmap(t_scene *scene, t_buffer_target target)
{
	cl_mem	buffer;
	void	**host_buffer;
	int		err;

	if (target == SHAPE_BUFFER_TARGET)
	{
		buffer = scene->shapebuffer;
		host_buffer = &scene->host_shapebuffer;
	}
	else if (target == LIGHT_BUFFER_TARGET)
	{
		buffer = scene->lightbuffer;
		host_buffer = &scene->host_lightbuffer;
	}
	else
	{
		print_error("Wrong target in scene unmap function");
		return ;
	}
	err = clEnqueueUnmapMemObject(g_clcontext.command_queue, buffer, *host_buffer, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		print_opencl_error("Failed to unmap buffer...", err);
	*host_buffer = NULL;
}

void	scene_add_sphere(t_scene *scene, t_shape *shape, const t_sphere *sphere)
{
	if (scene->shapebuffer_size + sizeof(t_shape) + sizeof(t_sphere) > SHAPEBUFFER_CAPACITY)
		print_error("Reached the maximum number of shapes in scene"); // TODO: don't exit the program just print message and return
	shape->buffer_offset = scene->shapebuffer_size;
	scene->shapebuffer_size += sizeof(t_shape) + sizeof(t_sphere);
	scene->nshapes++;
	ft_memcpy(scene->host_shapebuffer, shape, sizeof(t_shape));
	ft_memcpy(scene->host_shapebuffer + sizeof(t_shape), sphere, sizeof(t_sphere));
	scene->host_shapebuffer += sizeof(t_shape) + sizeof(t_sphere);
}

void	scene_update_sphere(t_scene *scene, const t_shape *shape, const t_sphere *sphere)
{
	(void)scene;
	(void)shape;
	(void)sphere;
	// TODO: implement
}

void	scene_add_plane(t_scene *scene, t_shape *shape, const t_plane *plane)
{
	if (scene->shapebuffer_size + sizeof(t_shape) + sizeof(t_plane) > SHAPEBUFFER_CAPACITY)
		print_error("Reached the maximum number of shapes in scene"); // TODO: don't exit the program just print message and return
	shape->buffer_offset = scene->shapebuffer_size;
	scene->shapebuffer_size += sizeof(t_shape) + sizeof(t_plane);
	scene->nshapes++;
	ft_memcpy(scene->host_shapebuffer, shape, sizeof(t_shape));
	ft_memcpy(scene->host_shapebuffer + sizeof(t_shape), plane, sizeof(t_plane));
	scene->host_shapebuffer += sizeof(t_shape) + sizeof(t_plane);
}

void	scene_update_plane(t_scene *scene, const t_shape *shape, const t_plane *plane)
{
	(void)scene;
	(void)shape;
	(void)plane;
	// TODO: implement
}

void	scene_remove(t_scene *scene, const t_shape *shape)
{
	(void)scene;
	(void)shape;
	// TODO: implement
}

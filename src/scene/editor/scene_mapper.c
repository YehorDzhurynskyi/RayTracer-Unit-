/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenebuffer_mapper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include "opencl.h"
#include "logger.h"
#include <assert.h>

static void	determine_target_buffers(t_scene *scene, cl_mem **device_buffer,
void ***host_buffer, t_buff_target target)
{
	if (target == SHAPEBUFF_TARGET)
	{
		*device_buffer = &scene->device_shapebuffer;
		*host_buffer = &scene->host_shapebuffer;
	}
	else if (target == LIGHTSOURCEBUFF_TARGET)
	{
		*device_buffer = &scene->device_lightsourcebuffer;
		*host_buffer = &scene->host_lightsourcebuffer;
	}
	else if (target == MATERIALBUFF_TARGET)
	{
		*device_buffer = &scene->device_materialbuffer;
		*host_buffer = &scene->host_materialbuffer;
	}
	else if (target == TEXTUREBUFF_TARGET)
	{
		*device_buffer = &scene->device_texturebuffer;
		*host_buffer = &scene->host_texturebuffer;
	}
	else
	{
		assert("Unrecognized target" == NULL);
	}
}

void		scenebuffer_map(t_scene *scene, int offset,
size_t size, t_buff_target target)
{
	int		err;
	cl_mem	*device_buffer;
	void	**host_buffer;

	assert(scene->mapped_host_buffer == NULL
	&& scene->mapped_device_buffer == NULL);
	determine_target_buffers(scene, &device_buffer, &host_buffer, target);
	scene->mapped_host_buffer = *host_buffer + offset;
	scene->mapped_device_buffer = clEnqueueMapBuffer(g_clcontext.command_queue,
	*device_buffer, CL_TRUE, CL_MAP_WRITE, offset, size, 0, NULL, NULL, &err);
	if (err != CL_SUCCESS)
		log_error(opencl_get_error(err), RT_OPENCL_ERROR);
}

void		scenebuffer_unmap(t_scene *scene, t_buff_target target)
{
	int		err;
	cl_mem	*device_buffer;
	void	**host_buffer;

	determine_target_buffers(scene, &device_buffer, &host_buffer, target);
	err = clEnqueueUnmapMemObject(g_clcontext.command_queue,
	*device_buffer, scene->mapped_device_buffer, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		log_error(opencl_get_error(err), RT_OPENCL_ERROR);
	scene->mapped_device_buffer = NULL;
	scene->mapped_host_buffer = NULL;
}

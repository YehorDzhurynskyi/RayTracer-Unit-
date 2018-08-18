/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "gui.h"
#include "logger.h"

static void		renderer_prepare(const t_scene *scene)
{
	int	err;

	err = clSetKernelArg(g_scene_renderer.rt_prgm.kernel, 0,
	sizeof(cl_mem), &g_scene_renderer.rt_prgm.outputbuffer);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	1, sizeof(cl_mem), &scene->device_shapebuffer);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	2, sizeof(cl_mem), &scene->device_lightsourcebuffer);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	3, sizeof(cl_mem), &scene->device_materialbuffer);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	4, sizeof(cl_mem), &scene->device_texturebuffer);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	5, sizeof(cl_mem), &scene->skybox);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	6, sizeof(cl_mem), &scene->textures);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	7, sizeof(t_scene_meta), &scene->meta);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	8, sizeof(t_scene_config), &scene->config);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel,
	9, sizeof(t_camera), &scene->camera);
	if (err)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
}

static void		prepare_filter(cl_mem **in_buffer, cl_mem **out_buffer, int i)
{
	int	err;

	*out_buffer = &g_scene_renderer.filter_prgms[i].outputbuffer;
	err = clSetKernelArg(g_scene_renderer.filter_prgms[i].kernel,
	0, sizeof(cl_mem), &**in_buffer);
	err |= clSetKernelArg(g_scene_renderer.filter_prgms[i].kernel,
	1, sizeof(cl_mem), &**out_buffer);
	if (err)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
}

static cl_mem	*enqueue_filters(int width, int height)
{
	int		err;
	int		i;
	cl_mem	*in_buffer;
	cl_mem	*out_buffer;

	in_buffer = &g_scene_renderer.rt_prgm.outputbuffer;
	out_buffer = &g_scene_renderer.rt_prgm.outputbuffer;
	i = -1;
	while (++i < RT_MAX_FILTERS)
	{
		if (g_scene_renderer.vfx_mask & (1 << i))
		{
			prepare_filter(&in_buffer, &out_buffer, i);
			err = clEnqueueNDRangeKernel(g_clcontext.command_queue,
			g_scene_renderer.filter_prgms[i].kernel,
			2, NULL, (size_t[]){width, height}, NULL, 0, NULL, NULL);
			if (err)
				log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
			in_buffer = &g_scene_renderer.filter_prgms[i].outputbuffer;
		}
	}
	return (out_buffer);
}

void			renderer_render(const t_scene *scene,
unsigned char *pixelbuffer, int width, int height)
{
	int		err;
	cl_mem	*outputbuffer_ptr;

	if (g_should_redraw_scene == FALSE)
		return ;
	renderer_prepare(scene);
	err = clEnqueueNDRangeKernel(g_clcontext.command_queue,
	g_scene_renderer.rt_prgm.kernel,
	2, NULL, (size_t[]){width, height}, NULL, 0, NULL, NULL);
	if (err)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	outputbuffer_ptr = enqueue_filters(width, height);
	clFinish(g_clcontext.command_queue);
	err = clEnqueueReadBuffer(g_clcontext.command_queue,
		*outputbuffer_ptr, CL_TRUE, 0, width * height * 4,
		pixelbuffer, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "error.h"

t_renderer	g_scene_renderer;

static void	renderer_prepare(void)
{
	int	err;

	err = clSetKernelArg(g_scene_renderer.rt_prgm.kernel, 0,
	sizeof(cl_mem), &g_scene_renderer.rt_prgm.outputbuffer);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel, 1, sizeof(cl_mem), &g_scene_renderer.scene.shapebuffer);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel, 2, sizeof(cl_int), &g_scene_renderer.scene.nshapes);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel, 3, sizeof(cl_mem), &g_scene_renderer.scene.lightbuffer);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel, 4, sizeof(cl_int), &g_scene_renderer.scene.nlights);
	err |= clSetKernelArg(g_scene_renderer.rt_prgm.kernel, 5, sizeof(t_camera), &g_scene_renderer.scene.camera);
	if (err)
		print_opencl_error("Failed to set kernel arguments...", err);
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
	while (++i < (int)g_scene_renderer.nfilters)
	{
		out_buffer = &g_scene_renderer.filter_prgms[i].outputbuffer;
		err = clSetKernelArg(g_scene_renderer.filter_prgms[i].kernel, 0, sizeof(cl_mem), &*in_buffer);
		err |= clSetKernelArg(g_scene_renderer.filter_prgms[i].kernel, 1, sizeof(cl_mem), &*out_buffer);
		if (err)
			print_opencl_error("Failed to set kernel arguments...", err);
		err = clEnqueueNDRangeKernel(g_clcontext.command_queue, g_scene_renderer.filter_prgms[i].kernel,
		2, NULL, (size_t[]){width, height}, NULL, 0, NULL, NULL);
		if (err)
			print_opencl_error("Failed to run filter kernel...", err);
		in_buffer = &g_scene_renderer.filter_prgms[i].outputbuffer;
	}
	return (out_buffer);
}

void	renderer_render(unsigned char *pixelbuffer, int width, int height)
{
	int			err;
	cl_mem		*outputbuffer_ptr;

	renderer_prepare();
	err = clEnqueueNDRangeKernel(g_clcontext.command_queue, g_scene_renderer.rt_prgm.kernel,
	2, NULL, (size_t[]){width, height}, NULL, 0, NULL, NULL);
	if (err)
		print_opencl_error("Failed to run kernel...", err);
	outputbuffer_ptr = enqueue_filters(width, height);
	clFinish(g_clcontext.command_queue);
	err = clEnqueueReadBuffer(g_clcontext.command_queue,
		*outputbuffer_ptr, CL_TRUE, 0, width * height * 4,
		pixelbuffer, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		print_opencl_error("Failed to read output buffer...", err);
}

void	renderer_init(void)
{
	opencl_init();
	g_scene_renderer.rt_prgm = opencl_program_create("src/opencl/kernel/raytracer.cl", "trace"); // TODO: replace hardcoded values
	g_scene_renderer.nfilters = 0;
	g_scene_renderer.scene = scene_create();
}

void	renderer_cleanup(void)
{
	int	i;

	scene_cleanup(&g_scene_renderer.scene);
	opencl_program_cleanup(&g_scene_renderer.rt_prgm);
	i = 0;
	while (i < (int)g_scene_renderer.nfilters)
		opencl_program_cleanup(&g_scene_renderer.filter_prgms[i++]);
	opencl_cleanup();
}

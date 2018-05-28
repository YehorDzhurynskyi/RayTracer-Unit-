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

#include <math.h>
#include <time.h>
#include <stdio.h>

static void	renderer_prepare(const t_renderer *renderer)
{
	int	err;

	err = clSetKernelArg(renderer->rt_prgm.kernel, 0,
	sizeof(cl_mem), &renderer->rt_prgm.outputbuffer);
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 1, sizeof(cl_mem), &renderer->scene.shapebuffer);
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 2, sizeof(cl_int), &renderer->scene.nshapes);
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 3, sizeof(cl_mem), &renderer->scene.lightbuffer);
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 4, sizeof(cl_int), &renderer->scene.nlights);
#if 0
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 5, sizeof(t_camera), &renderer->scene.camera);
#else
	static clock_t last = 0;
	clock_t now = clock();
	static float ellapsed = 0.0f;
	ellapsed += ((now - last) / 1000000.0f) * 1000.0;
	last = now;
	double x = ((int)ellapsed) % 1000 / 1000.0 * 2.0 * M_PI;
	double s = sin(x);
	double c = cos(x);
	t_clmat4x4 mat = {
		{c, 0.0f, s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-s, 0.0f, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}
	};
	const float d = 8.0f;
	t_clvec4	pos = {{s * d, s, c * d, 0.0}};
	t_camera	camera = (t_camera){mat, pos};
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 5, sizeof(t_camera), &camera); // TODO: replace with scene.camera
#endif
	if (err)
		print_opencl_error("Failed to set kernel arguments...", err);
	// TODO: add light related and other set kernel args
}

static cl_mem	*enqueue_filters(t_renderer *renderer, int width, int height)
{
	int		err;
	int		i;
	cl_mem	*in_buffer;
	cl_mem	*out_buffer;

	in_buffer = &renderer->rt_prgm.outputbuffer;
	out_buffer = &renderer->rt_prgm.outputbuffer;
	i = -1;
	while (++i < (int)renderer->nfilters)
	{
		out_buffer = &renderer->filter_prgms[i].outputbuffer;
		err = clSetKernelArg(renderer->filter_prgms[i].kernel, 0, sizeof(cl_mem), &*in_buffer);
		err |= clSetKernelArg(renderer->filter_prgms[i].kernel, 1, sizeof(cl_mem), &*out_buffer);
		if (err)
			print_opencl_error("Failed to set kernel arguments...", err);
		err = clEnqueueNDRangeKernel(g_clcontext.command_queue, renderer->filter_prgms[i].kernel,
		2, NULL, (size_t[]){width, height}, NULL, 0, NULL, NULL);
		if (err)
			print_opencl_error("Failed to run filter kernel...", err);
		in_buffer = &renderer->filter_prgms[i].outputbuffer;
	}
	return (out_buffer);
}

void	renderer_render(unsigned char *pixelbuffer, int width, int height, void *user_ptr)
{
	t_renderer	*renderer;
	int			err;
	cl_mem		*outputbuffer_ptr;

	renderer = (t_renderer*)user_ptr;
	renderer_prepare(renderer);
	err = clEnqueueNDRangeKernel(g_clcontext.command_queue, renderer->rt_prgm.kernel,
	2, NULL, (size_t[]){width, height}, NULL, 0, NULL, NULL);
	if (err)
		print_opencl_error("Failed to run kernel...", err);
	outputbuffer_ptr = enqueue_filters(renderer, width, height);
	clFinish(g_clcontext.command_queue);
	err = clEnqueueReadBuffer(g_clcontext.command_queue,
		*outputbuffer_ptr, CL_TRUE, 0, width * height * 4,
		pixelbuffer, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		print_opencl_error("Failed to read output buffer...", err);
}

t_renderer	renderer_init(void)
{
	t_renderer	renderer;

	opencl_init();
	renderer.rt_prgm = opencl_program_create("src/opencl/kernel/raytracer.cl", "trace"); // TODO: replace hardcoded values
	renderer.nfilters = 0;
	renderer.scene = scene_create();
	return (renderer);
}

void		renderer_cleanup(t_renderer *renderer)
{
	int	i;

	scene_cleanup(&renderer->scene);
	opencl_program_cleanup(&renderer->rt_prgm);
	i = 0;
	while (i < (int)renderer->nfilters)
		opencl_program_cleanup(&renderer->filter_prgms[i++]);
	opencl_cleanup();
}

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

	err = clSetKernelArg(renderer->rt_prgm.kernel, 1, sizeof(cl_mem), &renderer->scene.shapebuffer);
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 2, sizeof(cl_int), &renderer->scene.nshapes);
#if 0
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 3, sizeof(t_camera), &renderer->scene.camera);
#else
	static clock_t last = 0;
	clock_t now = clock();
	static float ellapsed = 0.0f;
	ellapsed += ((now - last) / 1000000.0f) * 1000.0;
	last = now;
	double x = ((int)ellapsed) % 10000 / 10000.0 * 2.0 * M_PI;
	double s = sin(x);
	double c = cos(x);
	t_clmat4x4 mat = {
		{c, 0.0f, s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-s, 0.0f, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}
	};
	const float d = 8.0;
	t_clvec4	pos = {{s * d, 1.0, c * d, 0.0}};
	t_camera	camera = (t_camera){mat, pos};
	err |= clSetKernelArg(renderer->rt_prgm.kernel, 3, sizeof(t_camera), &camera); // TODO: replace with scene.camera
#endif
	if (err)
		print_opencl_error("Failed to set kernel arguments...", err);
	// TODO: add light related and other set kernel args
}

void	renderer_render(unsigned char *pixelbuffer, int width, int height, void *user_ptr)
{
	t_renderer	*renderer;
	int			err;

	renderer = (t_renderer*)user_ptr;
	renderer_prepare(renderer);
	err = clEnqueueNDRangeKernel(g_clcontext.command_queue, renderer->rt_prgm.kernel,
	2, NULL, (size_t[]){width, height}, NULL, 0, NULL, NULL);
	if (err)
		print_opencl_error("Failed to run kernel...", err);

	clFinish(g_clcontext.command_queue);
	err = clEnqueueReadBuffer(g_clcontext.command_queue,
		renderer->rt_prgm.outputbuffer, CL_TRUE, 0, width * height * 4,
		pixelbuffer, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		print_opencl_error("Failed to read output buffer...", err);
}

t_renderer	renderer_init(void)
{
	t_renderer	renderer;
	int			err;

	opencl_init();
	renderer.rt_prgm = opencl_program_create("src/opencl/kernel/raytracer.cl", "trace"); // TODO: replace hardcoded values
	renderer.filter_prgms = NULL;
	err = clSetKernelArg(renderer.rt_prgm.kernel, 0,
	sizeof(cl_mem), &renderer.rt_prgm.outputbuffer);
	renderer.scene = scene_create();
	return (renderer);
}

void		renderer_cleanup(t_renderer *renderer)
{
	scene_cleanup(&renderer->scene);
	opencl_program_cleanup(&renderer->rt_prgm);
	//TODO: delete filters in loop
	opencl_cleanup();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "error.h"
#include "window.h"
#include "opencl.h"
#include <stdlib.h>

int	g_frame_width = 800;
int	g_frame_height = 600;

static const char	*parse_cli_arguments(int argc, const char *argv[])
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "-w"))
			g_frame_width = ++i < argc ? ft_atoi(argv[i]) : 0;
		else if (ft_strequ(argv[i], "-h"))
			g_frame_height = ++i < argc ? ft_atoi(argv[i]) : 0;
		else
			return (argv[i]);
		if (i >= argc || g_frame_width <= 0 || g_frame_height <= 0)
			print_error("Invalid command line argument\n" RT_USAGE);
	}
	return (NULL);
}

static void	render(unsigned char *pixelbuffer, int width, int height, void *user_ptr)
{
	int err;
	t_opencl_program *prgm = (t_opencl_program*)user_ptr;
	err = clEnqueueNDRangeKernel(g_clcontext.commands, prgm->kernel, 2, NULL, (size_t[]){800, 600}, NULL, 0, NULL, NULL);
	if (err)
		print_opencl_error("Failed to set kernel arguments...", err);
	clFinish(g_clcontext.commands);
	err = clEnqueueReadBuffer(g_clcontext.commands,
		prgm->outputbuffer, CL_TRUE, 0, width * height * 4,
		pixelbuffer, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		print_opencl_error("Failed to read output buffer...", err);
}

int			main(int argc, const char *argv[])
{
	const char		*scene_file;

	scene_file = parse_cli_arguments(argc, argv);
	(void)scene_file;
	if (window_create() == FALSE)
		return (EXIT_FAILURE);
	opencl_init();
	t_opencl_program prgm = opencl_program_create("src/opencl/kernel/raytracer.cl", "trace");
	int err;

	prgm.outputbuffer = clCreateBuffer(g_clcontext.context, CL_MEM_WRITE_ONLY, 800 * 600 * 4, NULL, &err);
	if (prgm.outputbuffer == NULL || err != CL_SUCCESS)
		print_opencl_error("Failed to create output buffer...", err);
	err = clSetKernelArg(prgm.kernel, 0, sizeof(cl_mem), &prgm.outputbuffer);
	if (err)
		print_opencl_error("Failed to set kernel arguments...", err);
	window_loop(render, &prgm);
	opencl_program_cleanup(&prgm);
	opencl_cleanup();
	return (EXIT_SUCCESS);
}

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
#include "renderer.h"
#include "scene.h"
#include "shape.h"
#include <stdlib.h>

int					g_frame_width = 800;
int					g_frame_height = 600;

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

int					main(int argc, const char *argv[])
{
	const char		*scene_file;
	t_renderer		renderer;

	scene_file = parse_cli_arguments(argc, argv);
	(void)scene_file;
	if (window_create() == FALSE)
		return (EXIT_FAILURE);
	renderer = renderer_init();

// DYNAMIC SCENE EDITING
	int err;
	renderer.scene.host_shapebuffer = clEnqueueMapBuffer(g_clcontext.command_queue, renderer.scene.shapebuffer,
	CL_TRUE, CL_MAP_WRITE, 0, (sizeof(t_shape) + sizeof(t_sphere)) * 2, 0, NULL, NULL, &err);
	if (err != CL_SUCCESS)
		print_opencl_error("Failed to map shapebuffer...", err);

	t_clvec4 position = {{1.0, 0.0, -1.0, 0.0}};
	cl_uchar4 color = {{0xff, 0xff, 0x0, 0x0}};
	t_shape shape = (t_shape) {position, color, 0, SPHERE};
	t_sphere sphere = (t_sphere) { 2.0f };
	scene_add_sphere(&renderer.scene, &shape, &sphere);

	t_clvec4 position3 = {{0.0, -2.0, 0.0, 0.0}};
	cl_uchar4 color3 = {{0x66, 0x44, 0x66, 0x0}};
	t_shape shape3 = (t_shape) {position3, color3, 0, PLANE};
	t_clvec4 normal1 = {{0.0, 1.0, 0.0, 0.0}};
	t_plane plane1 = (t_plane) { normal1 };
	scene_add_plane(&renderer.scene, &shape3, &plane1);

	t_clvec4 position1 = {{-1.0, 0.0, -1.0, 0.0}};
	cl_uchar4 color1 = {{0x00, 0xff, 0xff, 0x0}};
	t_shape shape1 = (t_shape) {position1, color1, 0, SPHERE};
	t_sphere sphere1 = (t_sphere) { 2.0f };
	scene_add_sphere(&renderer.scene, &shape1, &sphere1);

	t_clvec4 position2 = {{0.0, 0.0, -5.0, 0.0}};
	cl_uchar4 color2 = {{0xff, 0x00, 0xff, 0x0}};
	t_shape shape2 = (t_shape) {position2, color2, 0, PLANE};
	t_clvec4 normal = {{0.0, 0.0, 1.0, 0.0}};
	t_plane plane = (t_plane) { normal };
	scene_add_plane(&renderer.scene, &shape2, &plane);

	scene_unmap(&renderer.scene, SHAPE_BUFFER_TARGET);
// DYNAMIC SCENE EDITING

	window_loop(renderer_render, &renderer);

	renderer_cleanup(&renderer);
	return (EXIT_SUCCESS);
}

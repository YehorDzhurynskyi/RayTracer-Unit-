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

#include <math.h>

int					main(int argc, const char *argv[])
{
	const char		*scene_file;
	t_renderer		renderer;

	scene_file = parse_cli_arguments(argc, argv);
	(void)scene_file;
	if (window_create() == FALSE)
		return (EXIT_FAILURE);
	renderer = renderer_init();

	// renderer.filter_prgms[0] = opencl_program_create("src/opencl/kernel/filters/sepia_filter.cl", "filter");
	// renderer.nfilters++;
	// renderer.filter_prgms[0] = opencl_program_create("src/opencl/kernel/filters/bw_filter.cl", "filter");
	// renderer.nfilters++;
// DYNAMIC SCENE EDITING
	int err;
	renderer.scene.host_shapebuffer = clEnqueueMapBuffer(g_clcontext.command_queue, renderer.scene.shapebuffer,
	CL_TRUE, CL_MAP_WRITE, 0, (sizeof(t_shape) + sizeof(t_sphere)) * 2, 0, NULL, NULL, &err);
	if (err != CL_SUCCESS)
		print_opencl_error("Failed to map shapebuffer...", err);

	t_clvec4 position6 = {{0.0, 2.0, -3.0, 0.0}};
	cl_uchar4 color6 = {{0x22, 0x55, 0xdd, 0x0}};
	t_shape shape6 = (t_shape) {position6, color6, 0, 10.0f, 0.5f, CONE};
	const float cos2angle = cos(30.0f * M_PI / 180.0f) * cos(30.0f * M_PI / 180.0f);
	t_cone cone = (t_cone) { {{0.0f, 1.0f, 0.0f, 0.0f}}, cos2angle };
	scene_add_cone(&renderer.scene, &shape6, &cone);

	t_clvec4 position4 = {{-5.0, 0.0, 0.0, 0.0}};
	cl_uchar4 color4 = {{0x44, 0xaa, 0x44, 0x0}};
	t_shape shape4 = (t_shape) {position4, color4, 0, 20.0f, 0.1f, CYLINDER};
	t_cylinder cylinder = (t_cylinder) { {{-0.707f, 0.707f, 0.0f, 0.0f}}, 1.0f };
	scene_add_cylinder(&renderer.scene, &shape4, &cylinder);

	t_clvec4 position7 = {{-3.0, 2.0, 2.0, 0.0}};
	cl_uchar4 color7 = {{0xdd, 0x55, 0x33, 0x0}};
	t_shape shape7 = (t_shape) {position7, color7, 0, 1.0f, 0.0f, CONE};
	const float cos2angle1 = cos(10.0f * M_PI / 180.0f) * cos(10.0f * M_PI / 180.0f);
	t_cone cone1 = (t_cone) { {{0.0f, -0.707f, 0.707f, 0.0f}}, cos2angle1 };
	scene_add_cone(&renderer.scene, &shape7, &cone1);

	t_clvec4 position = {{1.0, 0.0, -1.0, 0.0}};
	cl_uchar4 color = {{0xff, 0xff, 0x0, 0x0}};
	t_shape shape = (t_shape) {position, color, 0, 4.0f, 0.0f, SPHERE};
	t_sphere sphere = (t_sphere) { 1.0f };
	scene_add_sphere(&renderer.scene, &shape, &sphere);

	t_clvec4 position3 = {{0.0, -2.0, 0.0, 0.0}};
	cl_uchar4 color3 = {{0x66, 0x44, 0x66, 0x0}};
	t_shape shape3 = (t_shape) {position3, color3, 0, 10.0f, 0.5f, PLANE};
	t_clvec4 normal1 = {{0.0, 1.0, 0.0, 0.0}};
	t_plane plane1 = (t_plane) { normal1 };
	scene_add_plane(&renderer.scene, &shape3, &plane1);

	t_clvec4 position1 = {{-1.0, 0.0, -1.0, 0.0}};
	cl_uchar4 color1 = {{0x00, 0xff, 0xff, 0x0}};
	t_shape shape1 = (t_shape) {position1, color1, 0, 7.0f, 0.0f, SPHERE};
	t_sphere sphere1 = (t_sphere) { 1.0f };
	scene_add_sphere(&renderer.scene, &shape1, &sphere1);

	t_clvec4 position8 = {{3.0, 2.0, 2.0, 0.0}};
	cl_uchar4 color8 = {{0xc4, 0xc2, 0xb4, 0x0}};
	t_shape shape8 = (t_shape) {position8, color8, 0, 5.0f, 0.7f, CONE};
	t_cone cone2 = (t_cone) { {{0.0f, -0.707f, -0.707f, 0.0f}}, cos2angle1 };
	scene_add_cone(&renderer.scene, &shape8, &cone2);

	t_clvec4 position5 = {{5.0, 0.0, 0.0, 0.0}};
	cl_uchar4 color5 = {{0x44, 0xaa, 0x44, 0x0}};
	t_shape shape5 = (t_shape) {position5, color5, 0, 25.0f, 0.6f, CYLINDER};
	t_cylinder cylinder1 = (t_cylinder) { {{0.707f, 0.707f, 0.0f, 0.0f}}, 1.0f };
	scene_add_cylinder(&renderer.scene, &shape5, &cylinder1);

	t_clvec4 position2 = {{0.0, 0.0, -5.0, 0.0}};
	cl_uchar4 color2 = {{0xff, 0x00, 0xff, 0x0}};
	t_shape shape2 = (t_shape) {position2, color2, 0, 30.0f, 0.4f, PLANE};
	t_clvec4 normal = {{0.0, 0.707f, 0.707f, 0.0}};
	t_plane plane = (t_plane) { normal };
	scene_add_plane(&renderer.scene, &shape2, &plane);

	t_clvec4 position9 = {{-100.0, 0.0, 0.0, 0.0}};
	cl_uchar4 color9 = {{0x33, 0xaa, 0x55, 0x0}};
	t_shape shape9 = (t_shape) {position9, color9, 0, 25.0f, 0.0f, PLANE};
	t_plane plane3 = (t_plane) { {{1.0, 0.0, 0.0, 0.0}} };
	scene_add_plane(&renderer.scene, &shape9, &plane3);

	scene_unmap(&renderer.scene, SHAPE_BUFFER_TARGET);
// DYNAMIC SCENE EDITING

// DYNAMIC LIGHT ADDING
	renderer.scene.host_lightbuffer = clEnqueueMapBuffer(g_clcontext.command_queue, renderer.scene.lightbuffer,
	CL_TRUE, CL_MAP_WRITE, 0, sizeof(t_light) + sizeof(t_pointlight), 0, NULL, NULL, &err);
	if (err != CL_SUCCESS)
		print_opencl_error("Failed to map lightbuffer...", err);

	t_light light = (t_light){{{0xff, 0xff, 0xff, 0}}, 0.7f, 0, POINTLIGHT};
	t_pointlight pointlight = (t_pointlight){{{5.0, 3.0, 10.0, 0.0}}, {{0.1, 0.05, 0.01, 0.0}}};
	scene_add_pointlight(&renderer.scene, &light, &pointlight);

	// const float cosangle = cos(60.0f * M_PI / 180.0f);

	// t_light light3 = (t_light){{{0xff, 0x33, 0x33, 0}}, 0.7f, 0, SPOTLIGHT};
	// t_spotlight spotlight = (t_spotlight){ {{-5.0, 3.0, 2.0, 0.0}}, {{1.0, 0.0, 0.0, 0.0}}, {{0.577f, -0.577f, -0.577f, 0.0f}}, cosangle };
	// scene_add_spotlight(&renderer.scene, &light3, &spotlight);

	// t_light light2 = (t_light){{{0xff, 0xff, 0x0, 0}}, 0.7f, 0, DIRLIGHT};
	// t_dirlight dirlight = (t_dirlight){ {{0.0, -0.707f, -0.707f, 0.0}} };
	// scene_add_dirlight(&renderer.scene, &light2, &dirlight);

	// t_light light4 = (t_light){{{0x33, 0x33, 0xff, 0}}, 0.7f, 0, SPOTLIGHT};
	// t_spotlight spotlight1 = (t_spotlight){ {{5.0, 3.0, 2.0, 0.0}}, {{1.0, 0.0, 0.0, 0.0}}, {{-0.577f, -0.577f, -0.577f, 0.0f}}, cosangle };
	// scene_add_spotlight(&renderer.scene, &light4, &spotlight1);

	t_light light1 = (t_light){{{0xff, 0xff, 0xff, 0}}, 0.7f, 0, POINTLIGHT};
	t_pointlight pointlight1 = (t_pointlight){{{-5.0, 3.0, 10.0, 0.0}}, {{0.1, 0.05, 0.01, 0.0}}};
	scene_add_pointlight(&renderer.scene, &light1, &pointlight1);

	scene_unmap(&renderer.scene, LIGHT_BUFFER_TARGET);
// DYNAMIC LIGHT ADDING

	window_loop(renderer_render, &renderer);

	renderer_cleanup(&renderer);
	return (EXIT_SUCCESS);
}

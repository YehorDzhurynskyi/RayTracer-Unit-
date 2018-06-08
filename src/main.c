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
#include "window.h"
#include "renderer.h"
#include "scene.h"
#include "sceneeditor.h"
#include "scenerepository.h"
#include "shape.h"
#include <stdlib.h>
#include "logger.h"

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
			log_fatal("Invalid command line argument\n" RT_USAGE,
			RT_COMMAND_LINE_PARSING_ERROR);
	}
	return (NULL);
}

int					main(int argc, const char *argv[])
{
	const char	*scene_file;
	t_err_code	err_code;

	scene_file = parse_cli_arguments(argc, argv);
	if (scene_file == NULL) // TODO: replace it later
	{
		ft_printf_fd(2, "usage: ./RT [-w framebuffer width] [-h framebuffer height] scene_file\n");
		return (EXIT_FAILURE);
	}
	renderer_init();
	window_create();
	err_code = scene_load(&g_scene_renderer.scene, scene_file);
	if (err_code != 0) // TODO: replace it later
	{
		ft_printf("Error has been occured with code %x\n", err_code);
		return (EXIT_FAILURE);
	}

	{
		// g_scene_renderer.filter_prgms[0] = opencl_program_create("src/opencl/kernel/filters/sepia_filter.cl", "filter");
		// g_scene_renderer.nfilters++;
		// g_scene_renderer.filter_prgms[0] = opencl_program_create("src/opencl/kernel/filters/bw_filter.cl", "filter");
		// g_scene_renderer.nfilters++;
	}

	window_loop(renderer_render);

	renderer_cleanup();
	return (EXIT_SUCCESS);
}

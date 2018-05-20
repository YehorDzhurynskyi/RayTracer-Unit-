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
	(void)user_ptr;
	for(unsigned int i = 0; i < 100000; i++)
	{
		const unsigned int x = rand() % width;
		const unsigned int y = rand() % height;

		const unsigned int offset = (width * 4 * y) + x * 4;
		const unsigned char channel = rand() % 256;
		pixelbuffer[offset + 0] = channel;
		pixelbuffer[offset + 1] = channel;
		pixelbuffer[offset + 2] = channel;
		pixelbuffer[offset + 3] = 0xff;
	}
}

int		main(int argc, const char *argv[])
{
	const char		*scene_file;

	scene_file = parse_cli_arguments(argc, argv);
	(void)scene_file;
	if (window_create() == FALSE)
		return (EXIT_FAILURE);
	window_loop(render, NULL);
	return (EXIT_SUCCESS);
}
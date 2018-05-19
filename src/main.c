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

#include <SDL.h>
#include "ft.h"
#include "error.h"

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

int					main(int argc, const char *argv[])
{
	const char *scene_file;

	scene_file = parse_cli_arguments(argc, argv);
	// SDL_Init(SDL_INIT_VIDEO);

	// SDL_Window *window = SDL_CreateWindow("SDL2Test",
	// 	SDL_WINDOWPOS_UNDEFINED,
	// 	SDL_WINDOWPOS_UNDEFINED,
	// 	640,
	// 	480,
	// 	0);

	// SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	// SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	// SDL_RenderClear(renderer);
	// SDL_RenderPresent(renderer);

	// SDL_Delay(3000);

	// SDL_DestroyWindow(window);
	// SDL_Quit();

	return 0;
}
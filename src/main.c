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

void render(SDL_Texture *texture)
{
	static unsigned char pixels[800 * 600 * 4] = {}; // replace hardcoded size
	for(unsigned int i = 0; i < 1000; i++)
	{
		const unsigned int x = rand() % 800;
		const unsigned int y = rand() % 600;

		const unsigned int offset = (800 * 4 * y) + x * 4;
		pixels[ offset + 0 ] = rand() % 256;
		pixels[ offset + 1 ] = rand() % 256;
		pixels[ offset + 2 ] = rand() % 256;
		pixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;
	}
	SDL_UpdateTexture(texture, NULL, pixels, 800 * 4);
}

int					main(int argc, const char *argv[])
{
	const char		*scene_file;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;

	const Uint64 freq = SDL_GetPerformanceFrequency();
	scene_file = parse_cli_arguments(argc, argv);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		print_error(SDL_GetError());
	window = SDL_CreateWindow("RT",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	g_frame_width, g_frame_height, 0);
	if (window == NULL)
	{
		SDL_Quit();
		print_error(SDL_GetError());
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		print_error(SDL_GetError());
	}
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, g_frame_width, g_frame_height);
	if (texture == NULL)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	t_bool window_should_close = FALSE;
	while (!window_should_close)
	{
		const Uint64 start = SDL_GetPerformanceCounter();
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				window_should_close = TRUE;
		}
		SDL_RenderClear(renderer);
		render(texture);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		// FPS counter
		const Uint64 end = SDL_GetPerformanceCounter();
		const double mseconds = (end - start) / (double)freq * 1000.0;
		ft_printf("FPS: %d, %fms\n", (int)(1000 / mseconds), mseconds);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
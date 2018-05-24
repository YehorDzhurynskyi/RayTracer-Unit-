/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <SDL.h>
#include "error.h"

static SDL_Window		*g_sdl_window = NULL;
static SDL_Renderer		*g_sdl_renderer = NULL;
static SDL_Texture		*g_sdl_texture = NULL;
static unsigned char	*g_pixelbuffer = NULL;
static t_bool			g_window_should_close = FALSE;

extern int				g_frame_width;
extern int				g_frame_height;

#define WINDOW_TITLE	"RT"

static void				window_cleanup(void)
{
	free(g_pixelbuffer);
	SDL_DestroyTexture(g_sdl_texture);
	SDL_DestroyRenderer(g_sdl_renderer);
	SDL_DestroyWindow(g_sdl_window);
	SDL_Quit();
}

t_bool					window_create(void)
{
	while (TRUE)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			break ;
		g_sdl_window = SDL_CreateWindow(WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		g_frame_width, g_frame_height, 0);
		if (g_sdl_window == NULL)
			break ;
		g_sdl_renderer = SDL_CreateRenderer(g_sdl_window, -1,
		SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/); // uncomment it on release
		if (g_sdl_renderer == NULL)
			break ;
		g_sdl_texture = SDL_CreateTexture(g_sdl_renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, g_frame_width, g_frame_height);
		if (g_sdl_texture == NULL)
			break ;
		g_pixelbuffer = (unsigned char*)malloc(g_frame_width * g_frame_height * 4);
		if (g_pixelbuffer == NULL)
			break ;
		return (TRUE);
	}
	window_cleanup();
	print_error(SDL_GetError());
	return (FALSE);
}

static void				poll_events(void)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			g_window_should_close = TRUE;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			g_window_should_close = TRUE;
	}
}

void					window_loop(t_render_callback render_callback, void *user_ptr)
{
	Uint64	start;
	Uint64	freq;
	double	mseconds;

	freq = SDL_GetPerformanceFrequency();
	while (!g_window_should_close)
	{
		start = SDL_GetPerformanceCounter();
		poll_events();
		SDL_RenderClear(g_sdl_renderer);
		ft_bzero(g_pixelbuffer, g_frame_width * g_frame_height * 4);
		render_callback(g_pixelbuffer, g_frame_width, g_frame_height, user_ptr);
		SDL_UpdateTexture(g_sdl_texture, NULL, g_pixelbuffer, g_frame_width * 4);
		SDL_RenderCopy(g_sdl_renderer, g_sdl_texture, NULL, NULL);
		SDL_RenderPresent(g_sdl_renderer);
		mseconds = (SDL_GetPerformanceCounter() - start) / (double)freq * 1000.0;
		ft_printf("FPS: %d, %fms\n", (int)(1000 / mseconds), mseconds);
	}
	window_cleanup();
}

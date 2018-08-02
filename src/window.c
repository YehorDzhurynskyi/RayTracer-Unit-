/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/06/11 14:54:17 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "ft.h"
#include "gui.h"
#include "logger.h"
#include "renderer.h"
#include <SDL_image.h>

static SDL_Window		*g_sdl_window = NULL;
static SDL_GLContext	*g_sdl_gl_context = NULL;
static GLuint			g_gl_render_target_name;

t_byte					*g_pixelbuffer = NULL;
t_bool					g_window_should_close = FALSE;

const int				g_frame_width = 800;
const int				g_frame_height = 600;

// https://www.opengl.org/discussion_boards/showthread.php/185739-Store-a-2D-texture-to-file

void					window_cleanup(void)
{
	free(g_pixelbuffer);
	if (g_sdl_gl_context != NULL)
		glDeleteTextures(1, &g_gl_render_target_name);
	if (g_sdl_gl_context != NULL)
		SDL_GL_DeleteContext(g_sdl_gl_context);
	if (g_sdl_window != NULL)
		SDL_DestroyWindow(g_sdl_window);
	SDL_Quit();
}

static void				generate_render_target()
{
	glGenTextures(1, &g_gl_render_target_name);
	glBindTexture(GL_TEXTURE_2D, g_gl_render_target_name);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, g_frame_width, g_frame_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

void					window_create(void)
{
	while (TRUE)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			break ;
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG); // TODO: check error
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, TRUE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		g_sdl_window = SDL_CreateWindow(RT_APP_NAME,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
		if (g_sdl_window == NULL)
			break ;
		g_sdl_gl_context = SDL_GL_CreateContext(g_sdl_window);
		if (g_sdl_gl_context == NULL)
			break ;
		g_pixelbuffer = (unsigned char*)malloc(g_frame_width * g_frame_height * 4); // TODO: change to 3 channel format
		if (g_pixelbuffer == NULL)
			break ;
		ft_bzero(g_pixelbuffer, g_frame_width * g_frame_height * 4);
		generate_render_target();
		return ;
	}
	window_cleanup();
	log_fatal("SDL window creation was failed", RT_SDL_ERROR);
}

void					window_loop(void)
{
	Uint64	start;
	Uint64	freq;
	float	mseconds;

	freq = SDL_GetPerformanceFrequency();
	glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
	gui_init(g_sdl_window, g_gl_render_target_name);
	while (!g_window_should_close)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		start = SDL_GetPerformanceCounter();
		gui_poll_events(&g_main_scene);
		renderer_render(&g_main_scene, g_pixelbuffer, g_frame_width, g_frame_height); // TODO: call this function every scene update
		glBindTexture(GL_TEXTURE_2D, g_gl_render_target_name);
		gui_render_scene(mseconds);
		gui_render();
		SDL_GL_SwapWindow(g_sdl_window);
		mseconds = (SDL_GetPerformanceCounter() - start) / (float)freq * 1000.0f;
	}
	gui_cleanup();
}

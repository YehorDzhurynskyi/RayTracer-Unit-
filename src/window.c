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


#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL2_IMPLEMENTATION
#define NK_PRIVATE

#include "nuklear.h"
#include "nuklear_sdl.h"
#include "renderer.h"

static SDL_Window			*g_sdl_window = NULL;
static SDL_GLContext		*g_sdl_gl_context = NULL;
struct nk_context			*g_nk_context = NULL;
static unsigned char		*g_pixelbuffer = NULL;
static t_bool				g_window_should_close = FALSE;
unsigned int				g_gl_texture_name;

extern int					g_frame_width;
extern int					g_frame_height;

#define WINDOW_TITLE	"RT"

//https://www.opengl.org/discussion_boards/showthread.php/185739-Store-a-2D-texture-to-file

void						window_cleanup(void)
{
	free(g_pixelbuffer);
	glDeleteTextures(1, &g_gl_texture_name);
	nk_sdl_shutdown();
	SDL_GL_DeleteContext(g_sdl_gl_context);
	SDL_DestroyWindow(g_sdl_window);
	SDL_Quit();
}

static void					generate_gl_texture()
{
	glGenTextures(1, &g_gl_texture_name);
	glBindTexture(GL_TEXTURE_2D, g_gl_texture_name);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, g_frame_width, g_frame_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

void						window_create(void)
{
	while (TRUE)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			break ;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		g_sdl_window = SDL_CreateWindow(WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1300, 900, SDL_WINDOW_OPENGL);
		if (g_sdl_window == NULL)
			break ;
		g_nk_context = nk_sdl_init(g_sdl_window);
		g_pixelbuffer = (unsigned char*)malloc(g_frame_width * g_frame_height * 4);
		if (g_pixelbuffer == NULL)
			break ;
		g_sdl_gl_context = SDL_GL_CreateContext(g_sdl_window);
		generate_gl_texture();
		struct nk_font_atlas *atlas;
		nk_sdl_font_stash_begin(&atlas);
		nk_sdl_font_stash_end();
		return ;
	}
	window_cleanup();
	log_fatal("SDL window creation was failed", RT_SDL_ERROR);
}

static void					poll_events(t_scene *scene)
{
	SDL_Event	event;

	if (g_main_scene != NULL)
		camera_key_handler(&scene->camera);
	nk_input_begin(g_nk_context);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			g_window_should_close = TRUE;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				g_window_should_close = TRUE;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			pick_shape(&event.button, scene);
		nk_sdl_handle_event(&event);
	}
	nk_input_end(g_nk_context);
}

static void					render_scene(void)
{
	struct nk_command_buffer	*canvas;
	struct nk_image				image;
	struct nk_rect				total_space;

	canvas = nk_window_get_canvas(g_nk_context);
	total_space = nk_window_get_content_region(g_nk_context);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_frame_width, g_frame_height, GL_RGBA, GL_UNSIGNED_BYTE, g_pixelbuffer);
	image = nk_image_id((int)g_gl_texture_name);
	nk_draw_image(canvas, total_space, &image, nk_rgba(255, 255, 255, 255));
}

void						window_loop(void)
{
	Uint64	start;
	Uint64	freq;
	double	mseconds;

	freq = SDL_GetPerformanceFrequency();
	ui_init_images();
	while (!g_window_should_close)
	{
		start = SDL_GetPerformanceCounter();
		poll_events(g_main_scene);
		renderer_render(g_main_scene, g_pixelbuffer, g_frame_width, g_frame_height); // TODO: call this function every scene update
		if (nk_begin(g_nk_context, "Scene", nk_rect(240, 5, 820, 640), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
		{
			glBindTexture(GL_TEXTURE_2D, g_gl_texture_name);
			render_scene();
		}
		nk_end(g_nk_context);
		render_gui();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.10f, 0.18f, 0.24f, 1.0f);
		nk_sdl_render(NK_ANTI_ALIASING_ON);
		SDL_GL_SwapWindow(g_sdl_window);
		mseconds = (SDL_GetPerformanceCounter() - start) / (double)freq * 1000.0;
		// ft_printf("FPS: %d, %fms\n", (int)(1000 / mseconds), mseconds);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/05/28 16:48:36 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

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

#define IMGNUM 5

#include <sys/stat.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include "nuklear.h"
#include "nuklear_sdl.h"

#include "targa.h"
#include <time.h>

extern struct nk_context	*g_nk_context;
struct nk_image				gui_images[11];
static unsigned int			g_gl_image_textures[11];
extern int					g_frame_width;
extern int					g_frame_height;

//make -C build
//./Debug/bin/RT
//перейти на ветку девеллоп
//git merge --squash gui_windows

void			ui_delete_images()
{
	glDeleteTextures(6, g_gl_image_textures);
}

void	screen_shot(void)
{
	time_t	now;
	t_byte	*pixels;
	char	*buff;
	char	*path;

	pixels = malloc(sizeof(t_byte) * ((g_frame_width * g_frame_height) * 3));
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	mkdir(RT_CWD "/Screenshots", S_IRWXU | S_IRWXG | S_IRWXO);
	time(&now);
	buff = ft_strjoin(ctime(&now), ".bmp");
	path = ft_strjoin(RT_CWD "/Screenshots/ ", buff);
	tga_write_rgb(path, pixels, (uint16_t)g_frame_width, (uint16_t)g_frame_height, 24);
	ft_strdel(&buff);
	ft_strdel(&path);
	free(pixels);
}

void	ui_init_images(void)
{
	int i;
	char buffer[32];

	i = 0;
	while (i < IMGNUM)
	{
		sprintf(buffer, "../../img/scr%d.bmp", i);
		g_gl_image_textures[i] = i;
		SDL_Surface *surf = SDL_LoadBMP(buffer);
		if (!surf && printf("No texture file\n"))
			exit(-1);
		glGenTextures(1, &g_gl_image_textures[i]);
		glBindTexture(GL_TEXTURE_2D, g_gl_image_textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
		gui_images[i] = nk_image_id(g_gl_image_textures[i]);
		SDL_FreeSurface(surf);
		i++;
	}
}

void	render_gui(void)
{	
		display_mainmnu();
		display_console();
		display_shapes_win();
		display_object_win();
		display_input_win();
}

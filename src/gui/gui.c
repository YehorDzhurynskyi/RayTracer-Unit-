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
#include "logger.h"

#define RT_GUI_IMG_NUM	9

struct nk_context	*g_nk_context = NULL;
struct nk_image		g_gui_images[RT_GUI_IMG_NUM];
struct nk_image		g_gui_render_target_image;

static GLuint		g_gl_image_textures[RT_GUI_IMG_NUM];

static void			gui_init_images(void)
{
	SDL_Surface	*surf;
	char		path[RT_GUI_RESOURCE_PATH_BUFF_LEN];
	int			prefix_len;
	int			i;

	ft_strncpy(path, RT_CWD "/assets/img/img", RT_GUI_RESOURCE_PATH_BUFF_LEN);
	prefix_len = ft_strlen(path);
	glGenTextures(RT_GUI_IMG_NUM, g_gl_image_textures);
	i = -1;
	while (++i < RT_GUI_IMG_NUM)
	{
		ft_itoa_cat(path + prefix_len, RT_GUI_RESOURCE_PATH_BUFF_LEN - prefix_len - 4, i);
		ft_strlcat(path, ".bmp", RT_GUI_RESOURCE_PATH_BUFF_LEN);
		surf = SDL_LoadBMP(path);
		if (surf == NULL)
			log_fatal("GUI Image loading error", RT_RESOURCE_LOADING_ERROR);
		glBindTexture(GL_TEXTURE_2D, g_gl_image_textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
		g_gui_images[i] = nk_image_id(g_gl_image_textures[i]);
		SDL_FreeSurface(surf);
	}
}

void				gui_init(SDL_Window *win, GLuint render_target)
{
	struct nk_font_atlas	*atlas;

	g_nk_context = nk_sdl_init(win);
	gui_init_style();
	nk_sdl_font_stash_begin(&atlas);
	nk_sdl_font_stash_end();
	gui_init_images();
	g_gui_render_target_image = nk_image_id((int)render_target);
}

void				gui_cleanup(void)
{
	nk_sdl_shutdown();
}

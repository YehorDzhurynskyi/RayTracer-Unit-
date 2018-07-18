/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_popups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 18:07:32 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 18:07:35 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <dirent.h>

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

#include <SDL.h>
#include <SDL_opengl.h>
#include "nuklear.h"
#include "nuklear_sdl.h"
#include "scene.h"

extern struct nk_context	*g_nk_context;
static int					g_scenes_active;
static int					g_diropened;
static char					g_chosen_scene[128];
static char					*g_scenes_buf;

void	display_scenes_list(void)
{
	int			i;
	static int	active;
	char		*scenes;

	i = 0;
	scenes = g_scenes_buf;
	while (*scenes)
	{
		if (nk_option_label(g_nk_context, scenes, active == i))
		{
			active = i;
			ft_strcpy(g_chosen_scene, scenes);
		}
		i++;
		scenes += ft_strlen(scenes) + 1;
	}
}

void	show_pop_scenes(int scenesnum)
{
	int scene_h;

	scene_h = (scenesnum / 2) * 30 + 45;
	if (nk_popup_begin(g_nk_context, NK_POPUP_STATIC, "Choose file", 0,
						nk_rect(400, 30, 450, scene_h)))
	{
		nk_layout_row_dynamic(g_nk_context, 25, 1);
		nk_label(g_nk_context, "Choose scene", NK_TEXT_LEFT);
		nk_layout_row_dynamic(g_nk_context, 25, 2);
		display_scenes_list();
	}
	nk_layout_row_dynamic(g_nk_context, 25, 2);
	if (nk_button_label(g_nk_context, "CANCEL") && !(g_diropened = 0))
	{
		g_scenes_active = 0;
		ft_strdel(&g_scenes_buf);
	}
	if (nk_button_label(g_nk_context, "CHANGE") && g_diropened)
	{
		scene_change(g_chosen_scene);
		g_scenes_active = 0;
		g_diropened = 0;
		ft_strdel(&g_scenes_buf);
	}
	nk_popup_end(g_nk_context);
}

int	load_scenes(int num)
{
	DIR				*d;
	struct dirent	*dir;
	char			*put;
	size_t			len;

	len = 0;
	d = opendir(SCENE_DIR);
	while ((dir = readdir(d)) != NULL)
		if (ft_strstr(dir->d_name, ".cson"))
			len += ft_strlen(dir->d_name) + 1;
	closedir(d);
	g_scenes_buf = ft_memalloc(sizeof(char) * len + 1);
	put = g_scenes_buf;
	d = opendir("scenes");
	while ((dir = readdir(d)) != NULL && ++num)
	{
		if (ft_strstr(dir->d_name, ".cson"))
		{
			ft_strcat(put, dir->d_name);
			put += ft_strlen(dir->d_name) + 1;
		}
	}
	ft_printf("NUM %d\n", num);
	closedir(d);
	return(num);
}

void	display_scenes(void)
{
	static int scenesnum;

	if (nk_button_label(g_nk_context, "Choose scene from file"))
		g_scenes_active = !g_scenes_active;
	if (g_scenes_active)
	{
		if (!g_diropened)
		{
			scenesnum = load_scenes(0);
			g_diropened = !g_diropened;
		}
		show_pop_scenes(scenesnum);
	}
}

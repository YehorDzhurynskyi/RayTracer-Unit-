/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_windows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:34:37 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 17:34:39 by pzubar           ###   ########.fr       */
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

#include <SDL.h>
#include <SDL_opengl.h>
#include "nuklear.h"
#include "nuklear_sdl.h"

extern struct nk_image gui_images[5];
extern struct nk_context *g_nk_context;

extern char *log_buf;

void display_fps(float	mseconds)
{
	// nk_layout_row_dynamic(g_nk_context, 30, 1);
	char string[64];
	int len = 5;
	char *buf;
	buf = nk_dtoa(string, (double)mseconds);
	nk_edit_string(g_nk_context, NK_EDIT_SIMPLE, buf, &len, 255, nk_filter_float);
	nk_layout_space_begin(g_nk_context, NK_STATIC, 20, 1);
	nk_layout_space_push(g_nk_context, nk_rect(SCENE_W - 132, 20, 100, 30));
	//v1
	nk_property_float(g_nk_context, "ms:", 0, &mseconds, 64.0f, 0.1f, 0.2f);
	//v2
	nk_edit_string(g_nk_context, NK_EDIT_SIMPLE, buf, &len, 255, nk_filter_float);
	nk_layout_space_end(g_nk_context);
	// ft_printf("FPS: %d, %fms\n", (int)(1000 / mseconds), mseconds);
}

void show_shapes(void)
{
	nk_layout_row_dynamic(g_nk_context, 75, 3);
	nk_image(g_nk_context, gui_images[3]);
	nk_image(g_nk_context, gui_images[4]);
	nk_image(g_nk_context, gui_images[4]);
	nk_layout_row_dynamic(g_nk_context, 20, 3);
	nk_label(g_nk_context, "Pyramid", NK_TEXT_LEFT);
	nk_label(g_nk_context, "Cone", NK_TEXT_LEFT);
	nk_label(g_nk_context, "Plane", NK_TEXT_LEFT);
	if (nk_button_label(g_nk_context, "Add"))
		ft_printf("Pyramid add\n");
	if (nk_button_label(g_nk_context, "Add"))
		ft_printf("Cone add\n");
	if (nk_button_label(g_nk_context, "Add"))
		ft_printf("Cone add\n");
}

void shapes_add_tree(void)
{
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Add Shape", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 75, 3);
		nk_image(g_nk_context, gui_images[0]);
		nk_image(g_nk_context, gui_images[1]);
		nk_image(g_nk_context, gui_images[2]);
		nk_layout_row_dynamic(g_nk_context, 20, 3);
		nk_label(g_nk_context, "Sphere", NK_TEXT_LEFT);
		nk_label(g_nk_context, "Cube", NK_TEXT_LEFT);
		nk_label(g_nk_context, "Cylinder", NK_TEXT_LEFT);
		if (nk_button_label(g_nk_context, "Add"))
			ft_printf("Sphere add\n");
		if (nk_button_label(g_nk_context, "Add"))
			ft_printf("Cube add\n");
		if (nk_button_label(g_nk_context, "Add"))
			ft_printf("Cylinder add\n");
		show_shapes();
		nk_tree_pop(g_nk_context);
	}
}

void display_mainmnu(void)
{
	if (nk_begin(g_nk_context, "Menu", nk_rect(MENU_X, MENU_Y, MENU_W, MENU_H),
				 NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Scene", NK_MAXIMIZED)) //ON RELEASE: Minimized
		{
			display_scenes();
			nk_layout_row_dynamic(g_nk_context, 25, 1);
			if (nk_button_label(g_nk_context, "Take-a-Snapshot"))
				scren_shot();
			nk_tree_pop(g_nk_context);
		}
		shapes_add_tree();
	}
	nk_end(g_nk_context);
}

void display_console(void)
{
	static int box_len;

	if (nk_begin(g_nk_context, "Information log", nk_rect(SCENE_X, 650,
		SCENE_W, 245),  NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE
		| NK_WINDOW_TITLE))
	{
		box_len = ft_strlen(log_buf);
		nk_layout_row_static(g_nk_context, 190, 790, 1);
		nk_edit_string(g_nk_context, NK_EDIT_BOX | NK_EDIT_SIG_ENTER, log_buf,
						&box_len, 4096, nk_filter_binary);
	}
	nk_end(g_nk_context);
}
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

void show_shapes_p2(void)
{
	nk_layout_row_dynamic(g_nk_context, 75, 2);
	nk_image(g_nk_context, gui_images[3]);
	nk_image(g_nk_context, gui_images[4]);
	nk_layout_row_dynamic(g_nk_context, 20, 2);
	nk_label(g_nk_context, "Pyramid", NK_TEXT_LEFT);
	nk_label(g_nk_context, "Cone", NK_TEXT_LEFT);
	if (nk_button_label(g_nk_context, "Add"))
		printf("Pyramid add");
	if (nk_button_label(g_nk_context, "Add"))
		printf("Cone add");
}
void show_shapes(void)
{
	nk_layout_row_dynamic(g_nk_context, 55, 3);
	nk_image(g_nk_context, gui_images[0]);
	nk_image(g_nk_context, gui_images[1]);
	nk_image(g_nk_context, gui_images[2]);
	nk_layout_row_dynamic(g_nk_context, 20, 3);
	nk_label_colored(g_nk_context, "Sphere", NK_TEXT_LEFT, nk_rgb(255, 255, 0));
	nk_label(g_nk_context, "Cube", NK_TEXT_LEFT);
	nk_label(g_nk_context, "Cylinder", NK_TEXT_LEFT);
	if (nk_button_label(g_nk_context, "Add"))
		printf("Sphere add");
	if (nk_button_label(g_nk_context, "Add"))
		printf("Cube add");
	if (nk_button_label(g_nk_context, "Add"))
		printf("Cylinder add");
	show_shapes_p2();
}

void shapes_tree(void)
{
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Add Shapes", NK_MAXIMIZED))
	{
		show_shapes();
		nk_tree_pop(g_nk_context);
	}
}

void display_mainmnu(void)
{
	if (nk_begin(g_nk_context, "Menu", nk_rect(10, 5, 220, 545),
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
		shapes_tree();
	}
	nk_end(g_nk_context);
}

void display_console(void)
{
	if (nk_begin(g_nk_context, "Information log", nk_rect(240, 650, 820, 245),
				 NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		static int box_len;
		box_len = ft_strlen(log_buf);
		nk_layout_row_static(g_nk_context, 190, 790, 1);
		nk_edit_string(g_nk_context, NK_EDIT_BOX | NK_EDIT_SIG_ENTER, log_buf,
					   &box_len, 4096, nk_filter_binary);
	}
	nk_end(g_nk_context);
}
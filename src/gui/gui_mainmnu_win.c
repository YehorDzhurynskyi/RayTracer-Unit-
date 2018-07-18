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

extern struct nk_image g_gui_images[9];
extern struct nk_context *g_nk_context;

extern char *g_log_buf;

void show_light(void)
{
	nk_layout_row_dynamic(g_nk_context, 75, 3);
	nk_image(g_nk_context, g_gui_images[6]);
	nk_image(g_nk_context, g_gui_images[7]);
	nk_image(g_nk_context, g_gui_images[8]);
	nk_layout_row_dynamic(g_nk_context, 20, 3);
	nk_label(g_nk_context, "Point", NK_TEXT_CENTERED);
	nk_label(g_nk_context, "Spot", NK_TEXT_CENTERED);
	nk_label(g_nk_context, "Directional", NK_TEXT_CENTERED);
	if (nk_button_label(g_nk_context, "Add"))
		ft_printf("Point add\n");
	if (nk_button_label(g_nk_context, "Add"))
		ft_printf("Spot light add\n");
	if (nk_button_label(g_nk_context, "Add"))
		ft_printf("Directional light add\n");
}

void show_shapes(void)
{
	nk_layout_row_dynamic(g_nk_context, 75, 3);
	nk_image(g_nk_context, g_gui_images[3]);
	nk_image(g_nk_context, g_gui_images[4]);
	nk_image(g_nk_context, g_gui_images[5]);
	nk_layout_row_dynamic(g_nk_context, 20, 3);
	nk_label(g_nk_context, "Pyramid", NK_TEXT_CENTERED);
	nk_label(g_nk_context, "Cone", NK_TEXT_CENTERED);
	nk_label(g_nk_context, "Plane", NK_TEXT_CENTERED);
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
		nk_image(g_nk_context, g_gui_images[0]);
		nk_image(g_nk_context, g_gui_images[1]);
		nk_image(g_nk_context, g_gui_images[2]);
		nk_layout_row_dynamic(g_nk_context, 20, 3);
		nk_label(g_nk_context, "Sphere", NK_TEXT_CENTERED);
		nk_label(g_nk_context, "Cube", NK_TEXT_CENTERED);
		nk_label(g_nk_context, "Cylinder", NK_TEXT_CENTERED);
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
	if (nk_begin(g_nk_context, "Menu", nk_rect(MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
	{
		display_opencl_choice();
		display_loading();
		if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Scene", NK_MAXIMIZED))
		{
			display_scenes();
			nk_layout_row_dynamic(g_nk_context, 25, 1);
			if (nk_button_label(g_nk_context, "Take-a-Snapshot"))
				screen_shot();
			nk_tree_pop(g_nk_context);
		}
		shapes_add_tree();
		if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Add Light", NK_MAXIMIZED))
		{
			show_light();
			nk_tree_pop(g_nk_context);
		}
	}
	nk_end(g_nk_context);
}

void display_console(void)
{
	static int box_len;

	if (nk_begin(g_nk_context, "Information log", nk_rect(LOG_X, LOG_Y, LOG_WIDTH, LOG_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
	{
		box_len = ft_strlen(g_log_buf);
		nk_layout_row_static(g_nk_context, 190, 790, 1);
		nk_edit_string(g_nk_context, NK_EDIT_BOX | NK_EDIT_SIG_ENTER, g_log_buf,
					   &box_len, 4096, nk_filter_binary);
	}
	nk_end(g_nk_context);
}

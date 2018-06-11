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

extern struct nk_context	*g_nk_context;

static void control_buttons(void)
{
	nk_button_set_behavior(g_nk_context, NK_BUTTON_REPEATER);
	nk_button_symbol(g_nk_context, NK_SYMBOL_CIRCLE_OUTLINE);
	nk_button_symbol(g_nk_context, NK_SYMBOL_TRIANGLE_UP) ?
		fprintf(stdout, "Move UP!\n") : 0;
	nk_button_symbol(g_nk_context, NK_SYMBOL_CIRCLE_OUTLINE);
	nk_button_symbol_label(g_nk_context, NK_SYMBOL_TRIANGLE_UP, "Inside",
		NK_TEXT_LEFT) ?	fprintf(stdout, "Move IN!\n") : 0;
	nk_button_symbol(g_nk_context, NK_SYMBOL_TRIANGLE_LEFT) ?
		fprintf(stdout, "Move LEFT!\n") : 0;
	nk_button_symbol(g_nk_context, NK_SYMBOL_TRIANGLE_DOWN) ?
		fprintf(stdout, "Move DOWN!\n") : 0;
	nk_button_symbol(g_nk_context, NK_SYMBOL_TRIANGLE_RIGHT) ?
		fprintf(stdout, "Move RIGHT!\n") : 0;
	nk_button_symbol_label(g_nk_context, NK_SYMBOL_TRIANGLE_DOWN, "Outside",
		NK_TEXT_LEFT) ?	fprintf(stdout, "Move OUT!\n") : 0;
	nk_button_set_behavior(g_nk_context, NK_BUTTON_DEFAULT);
}

void	display_mainmnu(void)
{
	if (nk_begin(g_nk_context, "Menu", nk_rect(10, 5, 220, 600),
			NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Scene", NK_MAXIMIZED)) //ON RELEASE: Minimized
		{
			nk_tree_pop(g_nk_context);
			display_scenes();
			nk_label(g_nk_context, "Move your eye in scene", NK_TEXT_LEFT);
			nk_layout_row_template_begin(g_nk_context, 0);
			nk_layout_row_template_push_static(g_nk_context, 28);
			nk_layout_row_template_push_static(g_nk_context, 28);
			nk_layout_row_template_push_static(g_nk_context, 28);
			nk_layout_row_template_push_static(g_nk_context, 95);
			control_buttons();
			nk_layout_row_template_end(g_nk_context);
			nk_layout_row_dynamic(g_nk_context, 25, 1);
			if (nk_button_label(g_nk_context, "Screenshot"))
				scren_shot();
		}
	}
	nk_end(g_nk_context);
}

void	display_console(void)
{
	if (nk_begin(g_nk_context, "Input Commands", nk_rect(240, 650, 820, 245),
	NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		static char text[100];
		static int text_len;
		static char box_buffer[1024];
		static int box_len;
		nk_flags active;
		nk_layout_row_static(g_nk_context, 30, 790, 1);
		active = nk_edit_string(g_nk_context, NK_EDIT_FIELD|NK_EDIT_SIG_ENTER,
			text, &text_len, 100, nk_filter_ascii);
		if (active & NK_EDIT_COMMITED)
		{
			text[text_len] = '\n';
			text_len++;
			memcpy(&box_buffer[box_len], &text, (nk_size)text_len);
			box_len += text_len;
			bzero(text, 100);
			text_len = 0;
		}
		nk_layout_row_static(g_nk_context, 150, 790, 1);
		nk_edit_string(g_nk_context, NK_EDIT_BOX|NK_EDIT_SIG_ENTER, box_buffer,
			&box_len, 512, nk_filter_binary);
	}
	nk_end(g_nk_context);
}
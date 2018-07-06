/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:43:12 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 17:43:14 by pzubar           ###   ########.fr       */
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

extern struct nk_context *g_nk_context;
static t_bool g_isloading;
static char g_message_buf[24];

void loading_message(char *message)
{
	g_isloading = TRUE;
	ft_strcpy(g_message_buf, message);
}
void loading_stop()
{
	g_isloading = FALSE;
}

void display_loading(void)
{
	if (g_isloading == TRUE &&nk_begin(g_nk_context, "Loading",
	nk_rect(500, 100, 0, 0), NK_WINDOW_TITLE))
	{
		nk_label(g_nk_context, g_message_buf, NK_TEXT_LEFT);
		nk_end(g_nk_context);
	}
}

void display_input_win(void)
{
	if (nk_begin(g_nk_context, "Input commands", nk_rect(X_CENTERED + 825, 550, 300, 345), //avoid calculation
				 NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		static char text[100];
		static int text_len;
		static char box_buffer[10];
		static int box_len;
		nk_flags active;
		nk_layout_row_static(g_nk_context, 30, 193, 1);
		active = nk_edit_string(g_nk_context, NK_EDIT_FIELD | NK_EDIT_SIG_ENTER,
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
		nk_layout_row_static(g_nk_context, 250, 193, 1);
		nk_edit_string(g_nk_context, NK_EDIT_BOX | NK_EDIT_SIG_ENTER, box_buffer,
					   &box_len, 512, nk_filter_binary);
	}
	nk_end(g_nk_context);
}
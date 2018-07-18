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

#define SHOW_SOLID nk_button_symbol(g_nk_context, NK_SYMBOL_CIRCLE_SOLID)
#define SHOW_OUTLINE nk_button_symbol(g_nk_context, NK_SYMBOL_CIRCLE_OUTLINE);

#include <SDL.h>
#include <SDL_opengl.h>
#include "nuklear.h"
#include "nuklear_sdl.h"

extern struct nk_context *g_nk_context;
static t_bool g_isloading = TRUE;

void	loading_stop(void)
{
	g_isloading = FALSE;
}

void	display_loading(void)
{
	static int	i = 1;
	static int	stage = 1;
	int			n;

	n = 0;
	if (g_isloading == TRUE && nk_popup_begin(g_nk_context, NK_POPUP_STATIC,
		"Loading", 0, nk_rect(POPUP_X, 200, POPUP_WIDTH, 110)))
	{
		nk_layout_row_dynamic(g_nk_context, 25, 1);
		nk_label(g_nk_context, "Loading, please wait", NK_TEXT_ALIGN_CENTERED);
		if (!(i % 150))
			i = 0;
		stage = (int)(i++ / 120.0 * 5);
		nk_layout_row_dynamic(g_nk_context, 25, 5);
		while (++n && n < 6)
			n == stage ? SHOW_SOLID : SHOW_OUTLINE;
		nk_layout_row_dynamic(g_nk_context, 25, 1);
		if (nk_button_label(g_nk_context, "close"))
			loading_stop();
	}
	nk_popup_end(g_nk_context);
}

void	display_fps(float mseconds)
{
	nk_layout_space_begin(g_nk_context, NK_STATIC, 20, 1);
	nk_layout_space_push(g_nk_context, nk_rect(20, 20, 100, 30));
	nk_labelf_colored(g_nk_context, NK_TEXT_LEFT, nk_red, "%4d fps",
		(int)(1000 / mseconds));
	nk_labelf_colored(g_nk_context, NK_TEXT_LEFT, nk_red, "%.2f ms", mseconds);
	nk_layout_space_end(g_nk_context);
}

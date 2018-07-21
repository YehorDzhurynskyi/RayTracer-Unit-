/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_loading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:43:12 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 17:43:14 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <dirent.h>

static t_bool	g_isloading = FALSE;
static char		g_loading_message[128];

void			gui_loading_start(const char *message)
{
	g_isloading = TRUE;
	ft_strncpy(g_loading_message, message, 128);
}

void			gui_loading_stop(void)
{
	g_isloading = FALSE;
}

void			gui_render_loading(void)
{
	static int	tick = 0;
	int			stage;
	int			n;

	if (g_isloading == FALSE)
		return ;
	if (nk_popup_begin(g_nk_context, NK_POPUP_STATIC,
		"Loading", 0, nk_rect(LOADING_POP_X, LOADING_POP_Y, LOADING_POP_WIDTH, 100)))
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label(g_nk_context, g_loading_message, NK_TEXT_ALIGN_CENTERED);
		stage = (int)(tick++ % 150 / 150.0 * 5);
		nk_layout_row_dynamic(g_nk_context, 25, 5);
		n = 0;
		while (n < 5)
		{
			if (n++ == stage)
				nk_button_symbol(g_nk_context, NK_SYMBOL_CIRCLE_SOLID);
			else
				nk_button_symbol(g_nk_context, NK_SYMBOL_CIRCLE_OUTLINE);
		}
	}
	nk_popup_end(g_nk_context);
}

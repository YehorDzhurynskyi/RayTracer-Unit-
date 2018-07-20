/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_info_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:34:37 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 17:34:39 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern char	*g_log_buf;

void	gui_render_info_log(void)
{
	static int box_len;

	if (nk_begin(g_nk_context, "Information log",
	nk_rect(LOG_X, LOG_Y, LOG_WIDTH, LOG_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
	{
		if (g_log_buf != NULL) // TODO: fix log buffer
		{
			box_len = ft_strlen(g_log_buf);
			nk_layout_row_static(g_nk_context, 190, 790, 1);
			nk_edit_string(g_nk_context, NK_EDIT_BOX | NK_EDIT_SIG_ENTER, g_log_buf,
						&box_len, 4096, nk_filter_binary);
		}
	}
	nk_end(g_nk_context);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_style.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/05/28 16:48:36 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	gui_init_style(void)
{
	struct nk_color	table[NK_COLOR_COUNT];

	table[NK_COLOR_TEXT] = nk_rgba(70, 70, 70, 255);
	table[NK_COLOR_WINDOW] = nk_rgba(238, 238, 238, 255);
	table[NK_COLOR_HEADER] = nk_rgba(253, 184, 19, 255);
	table[NK_COLOR_BORDER] = nk_rgba(200, 200, 200, 255);
	table[NK_COLOR_BUTTON] = nk_rgba(220, 220, 220, 255);
	table[NK_COLOR_BUTTON_HOVER] = nk_rgba(200, 200, 200, 255);
	table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(160, 160, 160, 255);
	table[NK_COLOR_TOGGLE] = nk_rgba(200, 200, 200, 255);
	table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(175, 175, 175, 255);
	table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(150, 150, 150, 255);
	table[NK_COLOR_SELECT] = nk_rgba(190, 190, 190, 255);
	table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(175, 175, 175, 255);
	table[NK_COLOR_SLIDER] = nk_rgba(190, 190, 190, 255);
	table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(80, 80, 80, 255);
	table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(70, 70, 70, 255);
	table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(60, 60, 60, 255);
	table[NK_COLOR_PROPERTY] = nk_rgba(220, 220, 220, 255);
	table[NK_COLOR_EDIT] = nk_rgba(230, 230, 230, 255);
	table[NK_COLOR_EDIT_CURSOR] = nk_rgba(0, 0, 0, 255);
	table[NK_COLOR_COMBO] = nk_rgba(220, 220, 220, 255);
	table[NK_COLOR_CHART] = nk_rgba(160, 160, 160, 255);
	table[NK_COLOR_CHART_COLOR] = nk_rgba(45, 45, 45, 255);
	table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
	table[NK_COLOR_SCROLLBAR] = nk_rgba(180, 180, 180, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(140, 140, 140, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(150, 150, 150, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(160, 160, 160, 255);
	table[NK_COLOR_TAB_HEADER] = nk_rgba(253, 184, 19, 255);
	nk_style_from_table(g_nk_context, table);
}

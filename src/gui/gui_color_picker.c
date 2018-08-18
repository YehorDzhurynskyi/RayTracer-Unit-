/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_color_picker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	gui_render_color_picker(struct nk_color *target_color)
{
	if (nk_combo_begin_color(g_nk_context, *target_color, nk_vec2(200, 400)))
	{
		nk_layout_row_dynamic(g_nk_context, 120, 1);
		*target_color = nk_rgba_cf(nk_color_picker(g_nk_context,
			nk_color_cf(*target_color), NK_RGBA));
		nk_layout_row_dynamic(g_nk_context, 25, 1);
		target_color->r = nk_propertyi(g_nk_context, "#R:", 0,
			target_color->r, 255, 1, 1);
		target_color->g = nk_propertyi(g_nk_context, "#G:", 0,
			target_color->g, 255, 1, 1);
		target_color->b = nk_propertyi(g_nk_context, "#B:", 0,
			target_color->b, 255, 1, 1);
		target_color->a = nk_propertyi(g_nk_context, "#A:", 0,
			target_color->a, 255, 1, 1);
		nk_combo_end(g_nk_context);
	}
}

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

void	gui_render_color_picker(struct nk_colorf *target_color)
{
	if (nk_combo_begin_color(g_nk_context, nk_rgb_cf(*target_color), nk_vec2(200, 400))) {
		nk_layout_row_dynamic(g_nk_context, 120, 1);
		*target_color = nk_color_picker(g_nk_context, *target_color, NK_RGBA);
		nk_layout_row_dynamic(g_nk_context, 25, 1);
		target_color->r = nk_propertyf(g_nk_context, "#R:", 0, target_color->r, 1.0f, 0.01f,0.005f);
		target_color->g = nk_propertyf(g_nk_context, "#G:", 0, target_color->g, 1.0f, 0.01f,0.005f);
		target_color->b = nk_propertyf(g_nk_context, "#B:", 0, target_color->b, 1.0f, 0.01f,0.005f);
		target_color->a = nk_propertyf(g_nk_context, "#A:", 0, target_color->a, 1.0f, 0.01f,0.005f);
		nk_combo_end(g_nk_context);
	}
}

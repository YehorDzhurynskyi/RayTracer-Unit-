/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_lightsource_form.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

void	render_lightsource_form(const t_lightsource *lightsource)
{
	static struct nk_colorf	light_color;
	static float			intensity;
	t_clcolor				color;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Lightsource", NK_MAXIMIZED))
	{
		intensity = lightsource->intensity;
		color = lightsource->color;
		light_color = (struct nk_colorf){ color.x / 255.0, color.y / 255.0, color.z / 255.0, color.w / 255.0 };
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label_colored(g_nk_context, "color", NK_TEXT_LEFT, nk_black);
		gui_render_color_picker(&light_color);
		nk_property_float(g_nk_context, "#intensity", 0.0f, &intensity, 1.0f, 0.1f, 0.1f);
		nk_tree_pop(g_nk_context);
	}
}

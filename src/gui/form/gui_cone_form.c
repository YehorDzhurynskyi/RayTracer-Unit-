/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_cone_form.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

void	render_cone_form(const t_cone *cone)
{
	static float	angle;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Cone", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		angle = (180.0 / M_PI) * acos(sqrt(cone->cos2angle));
		nk_property_float(g_nk_context, "#angle:", 0.0f,
			&angle, 180.0f, 1.0f, 1.0f);
		nk_tree_pop(g_nk_context);
	}
}

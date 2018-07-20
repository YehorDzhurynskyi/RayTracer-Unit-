/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_sphere_form.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

void	render_sphere_form(const t_sphere *sphere)
{
	static float	radius;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Sphere", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		radius = sqrt(sphere->radius2);
		nk_property_float(g_nk_context, "#radius:", 0.0f, &radius,
			INFINITY, 1.0f, 1.0f);
		nk_tree_pop(g_nk_context);
	}
}

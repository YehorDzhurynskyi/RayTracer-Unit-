/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_quadric_form.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

void	render_quadric_form(const t_shape *shape,
const t_quadric_surface *quadric)
{
	t_quadric_surface	new_quadric;

	(void)shape;
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Quadric", NK_MAXIMIZED))
	{
		new_quadric = *quadric;
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label_colored(g_nk_context,
		"Coefficients", NK_TEXT_LEFT, property_color);
		nk_tree_pop(g_nk_context);
	}
}

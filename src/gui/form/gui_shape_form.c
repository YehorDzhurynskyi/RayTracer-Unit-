/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_shape_form.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

static const char	*g_relation_type_names[] = {
	"Union",
	"Intersection",
	"Negation"
};

void				render_shape_form(const t_shape *shape)
{
	const t_primitive	*primitive;
	int					selected_relation_type;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Shape", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label_colored(g_nk_context, "relation type", NK_TEXT_LEFT, nk_black);
		selected_relation_type = nk_combo(g_nk_context, g_relation_type_names, 3,
		shape->relation_type - 1, 30, nk_vec2(190, 200));
		if (nk_button_label(g_nk_context, "Select material"))
			gui_select_object(shape->material_addr, MATERIALBUFF_TARGET);
		nk_tree_pop(g_nk_context);
	}
	primitive = shape_get_primitive(shape);
	render_primitive_form(primitive);
	render_actual_primitive_form(primitive);
}

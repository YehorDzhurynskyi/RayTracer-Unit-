/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_cylinder_form.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static void	update_cylinder(const t_shape *shape, const t_cylinder *old_cylinder,
const t_cylinder *new_cylinder)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_cylinder, new_cylinder, sizeof(t_cylinder)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, shape->addr + sizeof(t_shape) + sizeof(t_primitive),
	sizeof(t_cylinder), SHAPEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_cylinder, 0, sizeof(t_cylinder));
	scenebuffer_unmap(&g_main_scene, SHAPEBUFF_TARGET);
}

void	render_cylinder_form(const t_shape *shape, const t_cylinder *cylinder)
{
	t_cylinder	new_cylinder;
	float		radius;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Cylinder", NK_MAXIMIZED))
	{
		new_cylinder = *cylinder;
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		radius = sqrt(cylinder->radius2);
		nk_label_colored(g_nk_context, "radius", NK_TEXT_LEFT, property_color);
		nk_property_float(g_nk_context, "#value", 0.0f, &radius,
			INFINITY, 1.0f, 1.0f);
		new_cylinder.radius2 = radius * radius;
		update_cylinder(shape, cylinder, &new_cylinder);
		nk_tree_pop(g_nk_context);
	}
}

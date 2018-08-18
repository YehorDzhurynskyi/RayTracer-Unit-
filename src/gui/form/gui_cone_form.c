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
#include "sceneeditor.h"

static void	update_cone(const t_shape *shape, const t_cone *old_cone,
const t_cone *new_cone)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_cone, new_cone, sizeof(t_cone)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene,
		shape->addr + sizeof(t_shape) + sizeof(t_primitive),
	sizeof(t_cone), SHAPEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_cone, 0, sizeof(t_cone));
	scenebuffer_unmap(&g_main_scene, SHAPEBUFF_TARGET);
}

void		render_cone_form(const t_shape *shape, const t_cone *cone)
{
	t_cone	new_cone;
	float	angle;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Cone", NK_MAXIMIZED))
	{
		new_cone = *cone;
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		angle = (180.0 / M_PI) * acos(sqrt(cone->cos2angle));
		nk_label_colored(g_nk_context, "angle", NK_TEXT_LEFT, property_color);
		nk_property_float(g_nk_context, "#value", 1.0f,
			&angle, 89.0f, 1.0f, 1.0f);
		new_cone.cos2angle = cos(angle * M_PI / 180.0);
		new_cone.cos2angle *= new_cone.cos2angle;
		update_cone(shape, cone, &new_cone);
		nk_tree_pop(g_nk_context);
	}
}

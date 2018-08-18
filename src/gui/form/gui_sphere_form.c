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
#include "sceneeditor.h"

static void	update_sphere(const t_shape *shape, const t_sphere *old_sphere,
const t_sphere *new_sphere)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_sphere, new_sphere, sizeof(t_sphere)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene,
		shape->addr + sizeof(t_shape) + sizeof(t_primitive), sizeof(t_sphere),
		SHAPEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_sphere, 0, sizeof(t_sphere));
	scenebuffer_unmap(&g_main_scene, SHAPEBUFF_TARGET);
}

void		render_sphere_form(const t_shape *shape, const t_sphere *sphere)
{
	t_sphere	new_sphere;
	float		radius;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Sphere", NK_MAXIMIZED))
	{
		new_sphere = *sphere;
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		radius = sqrt(sphere->radius2);
		nk_label_colored(g_nk_context, "radius", NK_TEXT_LEFT, property_color);
		nk_property_float(g_nk_context, "#value", 0.0f, &radius,
			INFINITY, 1.0f, 1.0f);
		new_sphere.radius2 = radius * radius;
		update_sphere(shape, sphere, &new_sphere);
		nk_tree_pop(g_nk_context);
	}
}

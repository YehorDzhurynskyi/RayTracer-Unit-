/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_primitive_form.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

static void	render_primitive_position(const t_primitive *primitive)
{
	static float	xpos;
	static float	ypos;
	static float	zpos;

	xpos = primitive->position.x;
	ypos = primitive->position.y;
	zpos = primitive->position.z;
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "position", NK_TEXT_LEFT, nk_black);
	nk_property_float(g_nk_context, "#x:", -INFINITY, &xpos, INFINITY, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#y:", -INFINITY, &ypos, INFINITY, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#z:", -INFINITY, &zpos, INFINITY, 1.0f, 1.0f);
}

static void	render_primitive_orientation(const t_primitive *primitive)
{
	static float	rx;
	static float	ry;
	static float	rz;

	rx = atan2(primitive->orientation.s9, primitive->orientation.sa) *
		(180.0f / M_PI);
	const float a = sqrt(primitive->orientation.s9 * primitive->orientation.s9
		+ primitive->orientation.sa * primitive->orientation.sa);
	ry = atan2(-primitive->orientation.s8, a) * (180.0f / M_PI);
	rz = atan2(-primitive->orientation.s4, primitive->orientation.s0) *
		(180.0f / M_PI);
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "orientation", NK_TEXT_LEFT, nk_black);
	nk_property_float(g_nk_context, "#rotX:", -180.0f, &rx, 180.0f, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#rotY:", -180.0f, &ry, 180.0f, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#rotZ:", -180.0f, &rz, 180.0f, 1.0f, 1.0f);
}

void		render_primitive_form(const t_primitive *primitive)
{
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Primitive", NK_MAXIMIZED))
	{
		render_primitive_position(primitive);
		render_primitive_orientation(primitive);
		nk_tree_pop(g_nk_context);
	}
}

void		render_actual_primitive_form(const t_primitive *primitive)
{
	const t_byte	*actual;

	actual = primitive_get_actual(primitive);
	if (primitive->primitive_type == SPHERE)
		render_sphere_form((const t_sphere*)actual);
	else if (primitive->primitive_type == CYLINDER)
		render_cylinder_form((const t_cylinder*)actual);
	else if (primitive->primitive_type == CONE)
		render_cone_form((const t_cone*)actual);
}

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
#include "sceneeditor.h"

static void	render_primitive_position(t_primitive *primitive)
{
	float	xpos;
	float	ypos;
	float	zpos;

	xpos = primitive->position.x;
	ypos = primitive->position.y;
	zpos = primitive->position.z;
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "position", NK_TEXT_LEFT, property_color);
	nk_property_float(g_nk_context, "#x:",
		-INFINITY, &xpos, INFINITY, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#y:",
		-INFINITY, &ypos, INFINITY, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#z:",
		-INFINITY, &zpos, INFINITY, 1.0f, 1.0f);
	primitive->position.x = xpos;
	primitive->position.y = ypos;
	primitive->position.z = zpos;
}

static void	render_primitive_orientation(t_primitive *primitive)
{
	t_vec3f	rotations;
	float	a;

	rotations.x = atan2(primitive->orientation.s9, primitive->orientation.sa) *
		(180.0f / M_PI);
	a = sqrt(primitive->orientation.s9 * primitive->orientation.s9
		+ primitive->orientation.sa * primitive->orientation.sa);
	rotations.y = atan2(-primitive->orientation.s8, a) * (180.0f / M_PI);
	rotations.z = -atan2(-primitive->orientation.s4,
		primitive->orientation.s0) * (180.0f / M_PI);
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "orientation", NK_TEXT_LEFT, property_color);
	nk_property_float(g_nk_context, "#rotX:",
		-180.0f, &rotations.x, 180.0f, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#rotY:",
		-180.0f, &rotations.y, 180.0f, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#rotZ:",
		-180.0f, &rotations.z, 180.0f, 1.0f, 1.0f);
	primitive->orientation = to_orientation_matrix(rotations.x,
	rotations.y, rotations.z);
}

static void	update_primitive(const t_shape *shape,
const t_primitive *old_primitive,
const t_primitive *new_primitive)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_primitive, new_primitive,
		sizeof(t_primitive)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, shape->addr + sizeof(t_shape),
	sizeof(t_primitive), SHAPEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_primitive,
		0, sizeof(t_primitive));
	scenebuffer_unmap(&g_main_scene, SHAPEBUFF_TARGET);
}

void		render_primitive_form(const t_shape *shape,
	const t_primitive *primitive)
{
	t_primitive	new_primitive;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Primitive", NK_MAXIMIZED))
	{
		new_primitive = *primitive;
		render_primitive_position(&new_primitive);
		render_primitive_orientation(&new_primitive);
		update_primitive(shape, primitive, &new_primitive);
		nk_tree_pop(g_nk_context);
	}
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	render_actual_primitive_form(shape, primitive);
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	render_limitations(shape, primitive);
}

void		render_actual_primitive_form(const t_shape *shape,
	const t_primitive *primitive)
{
	const t_byte	*actual;

	actual = primitive_get_actual(primitive);
	if (primitive->primitive_type == SPHERE)
		render_sphere_form(shape, (const t_sphere*)actual);
	else if (primitive->primitive_type == CYLINDER)
		render_cylinder_form(shape, (const t_cylinder*)actual);
	else if (primitive->primitive_type == CONE)
		render_cone_form(shape, (const t_cone*)actual);
	else if (primitive->primitive_type == QUADRIC)
		render_quadric_form(shape, (const t_quadric_surface*)actual);
}

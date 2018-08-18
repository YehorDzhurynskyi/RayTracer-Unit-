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
#include "sceneeditor.h"

static const char	*g_relation_names[] = {
	"Union",
	"Intersection",
	"Negation"
};

void				render_children(const t_shape *shape)
{
	(void)shape;
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Children", NK_MINIMIZED))
	{
		if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS,
			"Add child", NK_TEXT_ALIGN_RIGHT))
		{
		}
		nk_tree_pop(g_nk_context);
	}
}

void				update_shape(const t_shape *old_shape,
const t_shape *new_shape)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_shape, new_shape, sizeof(t_shape)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, new_shape->addr,
	sizeof(t_shape), SHAPEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_shape, 0, sizeof(t_shape));
	scenebuffer_unmap(&g_main_scene, SHAPEBUFF_TARGET);
}

static void			render_absent_material(t_bool *render_chooser,
const t_material *material, t_shape *new_shape)
{
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS,
	"Set material", NK_TEXT_ALIGN_RIGHT))
		*render_chooser = TRUE;
	if (*render_chooser)
	{
		*render_chooser = gui_choose_material(&material);
		if (*render_chooser == FALSE && material != NULL)
			new_shape->material_addr = material->addr;
	}
}

static void			render_present_material(t_shape *new_shape,
const t_shape *shape)
{
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_X,
	"Remove", NK_TEXT_ALIGN_RIGHT))
		new_shape->material_addr = DEFAULT_MATERIAL_ID;
	if (nk_button_label(g_nk_context, "Select material"))
		gui_select_object(shape->material_addr, MATERIALBUFF_TARGET);
}

void				render_shape_form(const t_shape *shape)
{
	t_shape				new_shape;
	const t_primitive	*primitive;
	static t_bool		render_chooser;
	const t_material	*material;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Shape", NK_MAXIMIZED))
	{
		new_shape = *shape;
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label_colored(g_nk_context, "relation type",
		NK_TEXT_LEFT, property_color);
		new_shape.relation_type = 1 + nk_combo(g_nk_context, g_relation_names,
		3, shape->relation_type - 1, 30, nk_vec2(190, 200));
		if (shape->material_addr == DEFAULT_MATERIAL_ID)
			render_absent_material(&render_chooser, material, &new_shape);
		else
			render_present_material(&new_shape, shape);
		update_shape(shape, &new_shape);
		nk_tree_pop(g_nk_context);
	}
	primitive = shape_get_primitive(shape);
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	render_primitive_form(shape, primitive);
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	render_children(shape);
}

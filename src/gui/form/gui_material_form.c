/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_material_form.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static void	render_absent_normal_map_form(t_material *material)
{
	const t_texture	*texture;
	static t_bool	render_chooser;

	if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS,
	"Set normal map texture", NK_TEXT_ALIGN_RIGHT))
		render_chooser = TRUE;
	if (render_chooser)
	{
		render_chooser = gui_choose_texture(&texture);
		if (render_chooser == FALSE && texture != NULL)
		{
			material->mask |= NORMAL_MAP_MASK;
			material->normal_map = texture->addr;
		}
	}
}

static void	render_present_normal_map_form(t_material *material)
{
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_X,
	"Remove", NK_TEXT_ALIGN_RIGHT))
		material->mask &= ~NORMAL_MAP_MASK;
	if (nk_button_label(g_nk_context, "Select texture"))
		gui_select_object(material->normal_map, TEXTUREBUFF_TARGET);
}

static void	render_normal_map_form(t_material *material)
{
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "normal map",
	NK_TEXT_LEFT, property_color);
	if (HAS_NORMAL_MAP(material->mask))
	{
		render_present_normal_map_form(material);
	}
	else
	{
		render_absent_normal_map_form(material);
	}
}

static void	update_material(const t_material *old_material,
const t_material *new_material)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_material, new_material, sizeof(t_material)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, new_material->addr,
	sizeof(t_material), MATERIALBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_material, 0, sizeof(t_material));
	scenebuffer_unmap(&g_main_scene, MATERIALBUFF_TARGET);
}

void		render_material_form(const t_material *material)
{
	t_material	new_material;
	float		ior;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Material", NK_MAXIMIZED))
	{
		new_material = *material;
		ior = new_material.ior;
		render_diffuse_albedo_form(&new_material);
		render_specular_albedo_form(&new_material);
		render_glossiness_form(&new_material);
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label_colored(g_nk_context, "IOR", NK_TEXT_LEFT, property_color);
		nk_property_float(g_nk_context, "#value", 0.1f, &ior, 3.0f, 0.1f, 0.1f);
		new_material.ior = ior;
		render_normal_map_form(&new_material);
		update_material(material, &new_material);
		nk_tree_pop(g_nk_context);
	}
}

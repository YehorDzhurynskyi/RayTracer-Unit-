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

#define MONO_ALBEDO		1
#define TEXTURED_ALBEDO	2

#define CONST_SCALAR	1
#define TEXTURED_SCALAR	2

static void	render_color_variant_form(const char *caption, struct nk_colorf *color)
{
	int	albedo_type;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, caption, NK_TEXT_LEFT, nk_black);
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	albedo_type = MONO_ALBEDO; // TODO: retrieve albedo type from material mask
	albedo_type = nk_option_label(g_nk_context, "Monolete", albedo_type == MONO_ALBEDO) ? MONO_ALBEDO : albedo_type;
	albedo_type = nk_option_label(g_nk_context, "Textured", albedo_type == TEXTURED_ALBEDO) ? TEXTURED_ALBEDO : albedo_type;
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	if (albedo_type == MONO_ALBEDO)
		gui_render_color_picker(color);
}

static void	render_scalar_variant_form(const char *caption, float *scalar)
{
	int	scalar_type;

	nk_layout_row_dynamic(g_nk_context, 30, 2);
	scalar_type = CONST_SCALAR; // TODO: retrieve albedo type from material mask
	scalar_type = nk_option_label(g_nk_context, "Constant", scalar_type == CONST_SCALAR) ? CONST_SCALAR : scalar_type;
	scalar_type = nk_option_label(g_nk_context, "Textured", scalar_type == TEXTURED_SCALAR) ? TEXTURED_SCALAR : scalar_type;
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	if (scalar_type == CONST_SCALAR)
		nk_property_float(g_nk_context, caption, 0.0f, scalar, 1.0f, 0.1f, 0.1f);
}

void		render_material_form(const t_material *material)
{
	// TODO: process meterial mask
	static struct nk_colorf diffuse_albedo;
	static struct nk_colorf specular_albedo;
	static float			glossiness;
	static float			ior;
	t_clcolor				diffuse;
	t_clcolor				specular;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Material", NK_MAXIMIZED))
	{
		diffuse = material->diffuse_albedo.color;
		specular = material->specular_albedo.color;
		diffuse_albedo = (struct nk_colorf){ diffuse.x / 255.0, diffuse.y / 255.0, diffuse.z / 255.0, diffuse.w / 255.0 };
		specular_albedo = (struct nk_colorf){ specular.x / 255.0, specular.y / 255.0, specular.z / 255.0, specular.w / 255.0 };
		glossiness = material->glossiness.value;
		ior = material->ior;
		render_color_variant_form("diffuse albedo", &diffuse_albedo);
		render_color_variant_form("specular albedo", &specular_albedo);
		render_scalar_variant_form("glossiness", &glossiness);
		nk_property_float(g_nk_context, "#IOR", 0.0f, &ior, 1.0f, 0.1f, 0.1f);
		nk_tree_pop(g_nk_context);
	}
}

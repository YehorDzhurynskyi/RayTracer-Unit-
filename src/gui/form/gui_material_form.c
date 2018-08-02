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

#define MONO_ALBEDO		0
#define TEXTURED_ALBEDO	1

#define CONST_SCALAR	0
#define TEXTURED_SCALAR	1

static void	render_glossiness_form(t_material *material)
{
	static int		scalar_type;
	float			glossiness;
	const t_texture	*texture;
	static t_bool	render_chooser;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "glossiness", NK_TEXT_LEFT, property_color);
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	glossiness = material->glossiness.value;
	scalar_type = nk_option_label(g_nk_context, "Constant", scalar_type == CONST_SCALAR) ? CONST_SCALAR : scalar_type;
	scalar_type = nk_option_label(g_nk_context, "Textured", scalar_type == TEXTURED_SCALAR) ? TEXTURED_SCALAR : scalar_type;
	if (scalar_type == CONST_SCALAR)
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		if (!GLOSSINESS_IS_TEX(material->mask))
		{
			nk_property_float(g_nk_context, "#value", 0.0f, &glossiness, 1.0f, 0.1f, 0.1f);
			material->glossiness.value = glossiness;
		}
		else
		{
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS, "Set glossiness const value", NK_TEXT_ALIGN_RIGHT))
			{
				material->glossiness.value = 0.0f;
				material->mask &= ~GLOSSINESS_MASK;
			}
		}
	}
	else if (scalar_type == TEXTURED_SCALAR)
	{
		if (GLOSSINESS_IS_TEX(material->mask))
		{
			nk_layout_row_dynamic(g_nk_context, 30, 2);
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_X, "Remove", NK_TEXT_ALIGN_RIGHT))
			{
				material->glossiness.value = 0.0f;
				material->mask &= ~GLOSSINESS_MASK;
			}
			if (nk_button_label(g_nk_context, "Select texture"))
				gui_select_object(material->glossiness.tex_addr, TEXTUREBUFF_TARGET);
		}
		else
		{
			nk_layout_row_dynamic(g_nk_context, 30, 1);
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS, "Set glossiness texture", NK_TEXT_ALIGN_RIGHT))
				render_chooser = TRUE;
			if (render_chooser)
			{
				render_chooser = gui_choose_texture(&texture);
				if (render_chooser == FALSE && texture != NULL)
				{
					material->mask |= GLOSSINESS_MASK;
					material->glossiness.tex_addr = texture->addr;
				}
			}
		}
	}
}

static void	render_diffuse_albedo_form(t_material *material)
{
	static int		albedo_type;
	struct nk_color	diffuse_albedo;
	const t_texture	*texture;
	static t_bool	render_chooser;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "diffuse albedo", NK_TEXT_LEFT, property_color);
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	diffuse_albedo = to_nkcolor(material->diffuse_albedo.color);
	albedo_type = nk_option_label(g_nk_context, "Monolete", albedo_type == MONO_ALBEDO) ? MONO_ALBEDO : albedo_type;
	albedo_type = nk_option_label(g_nk_context, "Textured", albedo_type == TEXTURED_ALBEDO) ? TEXTURED_ALBEDO : albedo_type;
	if (albedo_type == MONO_ALBEDO)
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		if (!DIFFUSE_IS_TEX(material->mask))
		{
			gui_render_color_picker(&diffuse_albedo);
			material->diffuse_albedo.color = from_nkcolor(diffuse_albedo);
		}
		else
		{
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS, "Set diffuse monolete color", NK_TEXT_ALIGN_RIGHT))
			{
				material->diffuse_albedo.color = (t_clcolor){{ 0x0, 0x0, 0x0, 0x0 }};
				material->mask &= ~DIFFUSE_MASK;
			}
		}
	}
	else if (albedo_type == TEXTURED_ALBEDO)
	{
		if (DIFFUSE_IS_TEX(material->mask))
		{
			nk_layout_row_dynamic(g_nk_context, 30, 2);
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_X, "Remove", NK_TEXT_ALIGN_RIGHT))
			{
				material->diffuse_albedo.color = (t_clcolor){{ 0x0, 0x0, 0x0, 0x0 }};
				material->mask &= ~DIFFUSE_MASK;
			}
			if (nk_button_label(g_nk_context, "Select texture"))
				gui_select_object(material->diffuse_albedo.tex_addr, TEXTUREBUFF_TARGET);
		}
		else
		{
			nk_layout_row_dynamic(g_nk_context, 30, 1);
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS, "Set diffuse texture", NK_TEXT_ALIGN_RIGHT))
				render_chooser = TRUE;
			if (render_chooser)
			{
				render_chooser = gui_choose_texture(&texture);
				if (render_chooser == FALSE && texture != NULL)
				{
					material->mask |= DIFFUSE_MASK;
					material->diffuse_albedo.tex_addr = texture->addr;
				}
			}
		}
	}
}

static void	render_specular_albedo_form(t_material *material)
{
	static int		albedo_type;
	struct nk_color	specular_albedo;
	const t_texture	*texture;
	static t_bool	render_chooser;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "specular albedo", NK_TEXT_LEFT, property_color);
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	specular_albedo = to_nkcolor(material->specular_albedo.color);
	albedo_type = nk_option_label(g_nk_context, "Monolete", albedo_type == MONO_ALBEDO) ? MONO_ALBEDO : albedo_type;
	albedo_type = nk_option_label(g_nk_context, "Textured", albedo_type == TEXTURED_ALBEDO) ? TEXTURED_ALBEDO : albedo_type;
	if (albedo_type == MONO_ALBEDO)
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		if (!SPECULAR_IS_TEX(material->mask))
		{
			gui_render_color_picker(&specular_albedo);
			material->specular_albedo.color = from_nkcolor(specular_albedo);
		}
		else
		{
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS, "Set specular monolete color", NK_TEXT_ALIGN_RIGHT))
			{
				material->specular_albedo.color = (t_clcolor){{ 0x0, 0x0, 0x0, 0x0 }};
				material->mask &= ~SPECULAR_MASK;
			}
		}
	}
	else if (albedo_type == TEXTURED_ALBEDO)
	{
		if (SPECULAR_IS_TEX(material->mask))
		{
			nk_layout_row_dynamic(g_nk_context, 30, 2);
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_X, "Remove", NK_TEXT_ALIGN_RIGHT))
			{
				material->specular_albedo.color = (t_clcolor){{ 0x0, 0x0, 0x0, 0x0 }};
				material->mask &= ~SPECULAR_MASK;
			}
			if (nk_button_label(g_nk_context, "Select texture"))
				gui_select_object(material->specular_albedo.tex_addr, TEXTUREBUFF_TARGET);
		}
		else
		{
			nk_layout_row_dynamic(g_nk_context, 30, 1);
			if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS, "Set specular texture", NK_TEXT_ALIGN_RIGHT))
				render_chooser = TRUE;
			if (render_chooser)
			{
				render_chooser = gui_choose_texture(&texture);
				if (render_chooser == FALSE && texture != NULL)
				{
					material->mask |= SPECULAR_MASK;
					material->specular_albedo.tex_addr = texture->addr;
				}
			}
		}
	}
}

static void	render_normal_map_form(t_material *material)
{
	const t_texture	*texture;
	static t_bool	render_chooser;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "normal map", NK_TEXT_LEFT, property_color);
	if (HAS_NORMAL_MAP(material->mask))
	{
		nk_layout_row_dynamic(g_nk_context, 30, 2);
		if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_X, "Remove", NK_TEXT_ALIGN_RIGHT))
			material->mask &= ~NORMAL_MAP_MASK;
		if (nk_button_label(g_nk_context, "Select texture"))
			gui_select_object(material->normal_map, TEXTUREBUFF_TARGET);
	}
	else
	{
		if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS, "Set normal map texture", NK_TEXT_ALIGN_RIGHT))
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
}

static void	update_material(const t_material *old_material,
const t_material *new_material)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_material, new_material, sizeof(t_material)) == 0;
	if (up_to_date)
		return;
	scenebuffer_map(&g_main_scene, new_material->addr, sizeof(t_material), MATERIALBUFF_TARGET);
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

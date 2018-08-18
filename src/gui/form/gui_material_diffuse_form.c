/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_material_diffuse_form.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

#define MONO_ALBEDO		0
#define TEXTURED_ALBEDO	1

static void	render_monolith_diffuse_form(t_material *material)
{
	struct nk_color	diffuse_albedo;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	diffuse_albedo = to_nkcolor(material->diffuse_albedo.color);
	if (!DIFFUSE_IS_TEX(material->mask))
	{
		gui_render_color_picker(&diffuse_albedo);
		material->diffuse_albedo.color = from_nkcolor(diffuse_albedo);
	}
	else
	{
		if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS,
		"Set diffuse monolete color", NK_TEXT_ALIGN_RIGHT))
		{
			material->diffuse_albedo.color = (t_clcolor){{0x0, 0x0, 0x0, 0x0}};
			material->mask &= ~DIFFUSE_MASK;
		}
	}
}

static void	render_absent_diffuse_form(t_material *material)
{
	const t_texture	*texture;
	static t_bool	render_chooser;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS,
	"Set diffuse texture", NK_TEXT_ALIGN_RIGHT))
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

static void	render_present_diffuse_form(t_material *material)
{
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_X,
	"Remove", NK_TEXT_ALIGN_RIGHT))
	{
		material->diffuse_albedo.color = (t_clcolor){{ 0x0, 0x0, 0x0, 0x0 }};
		material->mask &= ~DIFFUSE_MASK;
	}
	if (nk_button_label(g_nk_context, "Select texture"))
	{
		gui_select_object(material->diffuse_albedo.tex_addr,
		TEXTUREBUFF_TARGET);
	}
}

void		render_diffuse_albedo_form(t_material *material)
{
	static int	albedo_type;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "diffuse albedo",
	NK_TEXT_LEFT, property_color);
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	albedo_type = nk_option_label(g_nk_context, "Monolete",
	albedo_type == MONO_ALBEDO) ? MONO_ALBEDO : albedo_type;
	albedo_type = nk_option_label(g_nk_context, "Textured",
	albedo_type == TEXTURED_ALBEDO) ? TEXTURED_ALBEDO : albedo_type;
	if (albedo_type == MONO_ALBEDO)
		render_monolith_diffuse_form(material);
	else if (albedo_type == TEXTURED_ALBEDO)
	{
		if (DIFFUSE_IS_TEX(material->mask))
		{
			render_present_diffuse_form(material);
		}
		else
		{
			render_absent_diffuse_form(material);
		}
	}
}

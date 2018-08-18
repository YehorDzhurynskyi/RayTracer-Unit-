/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_material_glossiness_form.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

#define CONST_SCALAR	0
#define TEXTURED_SCALAR	1

static void	render_constant_glossiness_form(t_material *material)
{
	float	glossiness;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	glossiness = material->glossiness.value;
	if (!GLOSSINESS_IS_TEX(material->mask))
	{
		nk_property_float(g_nk_context, "#value", 0.0f,
		&glossiness, 1.0f, 0.1f, 0.1f);
		material->glossiness.value = glossiness;
	}
	else
	{
		if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS,
		"Set glossiness const value", NK_TEXT_ALIGN_RIGHT))
		{
			material->glossiness.value = 0.0f;
			material->mask &= ~GLOSSINESS_MASK;
		}
	}
}

static void	render_absent_textured_glossiness_form(t_material *material)
{
	const t_texture	*texture;
	static t_bool	render_chooser;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS,
	"Set glossiness texture", NK_TEXT_ALIGN_RIGHT))
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

static void	render_present_textured_glossiness_form(t_material *material)
{
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_X,
	"Remove", NK_TEXT_ALIGN_RIGHT))
	{
		material->glossiness.value = 0.0f;
		material->mask &= ~GLOSSINESS_MASK;
	}
	if (nk_button_label(g_nk_context, "Select texture"))
	{
		gui_select_object(material->glossiness.tex_addr,
		TEXTUREBUFF_TARGET);
	}
}

void		render_glossiness_form(t_material *material)
{
	static int	scalar_type;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "glossiness", NK_TEXT_LEFT, property_color);
	nk_layout_row_dynamic(g_nk_context, 30, 2);
	scalar_type = nk_option_label(g_nk_context, "Constant",
		scalar_type == CONST_SCALAR) ? CONST_SCALAR : scalar_type;
	scalar_type = nk_option_label(g_nk_context, "Textured",
		scalar_type == TEXTURED_SCALAR) ? TEXTURED_SCALAR : scalar_type;
	if (scalar_type == CONST_SCALAR)
		render_constant_glossiness_form(material);
	else if (scalar_type == TEXTURED_SCALAR)
	{
		if (GLOSSINESS_IS_TEX(material->mask))
			render_present_textured_glossiness_form(material);
		else
			render_absent_textured_glossiness_form(material);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_texture_form.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static void	update_texture(const t_texture *old_texture,
	const t_texture *new_texture)
{
	t_bool	up_to_date;

	up_to_date = old_texture->scale == new_texture->scale
	&& old_texture->u_offset == new_texture->u_offset
	&& old_texture->v_offset == new_texture->v_offset;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, new_texture->addr,
		sizeof(t_texture), TEXTUREBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_texture, 0, sizeof(t_texture));
	scenebuffer_unmap(&g_main_scene, TEXTUREBUFF_TARGET);
}

static void	render_properties(t_texture *new_texture)
{
	float	scale;
	float	uoffset;
	float	voffset;

	scale = new_texture->scale;
	uoffset = new_texture->u_offset;
	voffset = new_texture->v_offset;
	nk_label_colored(g_nk_context, "Scale", NK_TEXT_LEFT, property_color);
	nk_property_float(g_nk_context,
		"#value", 1.0f, &scale, 20.0f, 0.1f, 0.1f);
	nk_label_colored(g_nk_context,
		"U Offset", NK_TEXT_LEFT, property_color);
	nk_property_float(g_nk_context,
		"#value", 0.0f, &uoffset, 1.0f, 0.01f, 0.01f);
	nk_label_colored(g_nk_context,
		"V Offset", NK_TEXT_LEFT, property_color);
	nk_property_float(g_nk_context,
		"#value", 0.0f, &voffset, 1.0f, 0.01f, 0.01f);
	new_texture->scale = scale;
	new_texture->u_offset = uoffset;
	new_texture->v_offset = voffset;
}

void		render_texture_form(const t_texture *texture)
{
	t_texture	new_texture;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Texture", NK_MAXIMIZED))
	{
		new_texture = *texture;
		render_properties(&new_texture);
		update_texture(texture, &new_texture);
		nk_tree_pop(g_nk_context);
	}
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	if (texture->texture_type == CHESS)
		render_chess_texture_form(texture);
	else if (texture->texture_type == CLIMAGE)
		render_climage_texture_form(texture);
}

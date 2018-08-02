/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_climage_form.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

void	render_climage_texture_form(const t_texture* texture)
{
	const t_climage_texture	*climage_texture;
	const char				*texture_name;

	climage_texture = (const t_climage_texture*)(texture + 1);
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Resource texture", NK_MAXIMIZED))
	{
		nk_label_colored(g_nk_context, "Texture name", NK_TEXT_LEFT, property_color);
		texture_name = texture_map_at(&g_main_scene.texture_map, climage_texture->tex_index);
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label(g_nk_context, texture_name, NK_TEXT_LEFT);
		nk_tree_pop(g_nk_context);
	}
}

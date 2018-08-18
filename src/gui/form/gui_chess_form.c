/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_chess_form.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static void	update_chess_texture(const t_texture *texture,
const t_chess_texture *old_chess_texture,
const t_chess_texture *new_chess_texture)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_chess_texture, new_chess_texture,
		sizeof(t_chess_texture)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, texture->addr + sizeof(t_texture),
	sizeof(t_chess_texture), TEXTUREBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_chess_texture, 0,
		sizeof(t_chess_texture));
	scenebuffer_unmap(&g_main_scene, TEXTUREBUFF_TARGET);
}

void		render_chess_texture_form(const t_texture *texture)
{
	t_chess_texture	new_chess_texture;
	struct nk_color	color1;
	struct nk_color	color2;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB,
		"Chessboard texture", NK_MAXIMIZED))
	{
		new_chess_texture = *((t_chess_texture*)(texture + 1));
		color1 = to_nkcolor(new_chess_texture.color1);
		color2 = to_nkcolor(new_chess_texture.color2);
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label_colored(g_nk_context, "First color",
			NK_TEXT_LEFT, property_color);
		gui_render_color_picker(&color1);
		nk_label_colored(g_nk_context, "Second color",
			NK_TEXT_LEFT, property_color);
		gui_render_color_picker(&color2);
		new_chess_texture.color1 = from_nkcolor(color1);
		new_chess_texture.color2 = from_nkcolor(color2);
		update_chess_texture(texture, (t_chess_texture*)(texture + 1),
			&new_chess_texture);
		nk_tree_pop(g_nk_context);
	}
}

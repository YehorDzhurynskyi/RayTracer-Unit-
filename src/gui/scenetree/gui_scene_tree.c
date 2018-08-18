/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:07:37 by pzubar            #+#    #+#             */
/*   Updated: 2018/06/30 18:07:39 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_scene_tree.h"

static void	render_items(void)
{
	if (nk_tree_push_id(g_nk_context, NK_TREE_TAB,
	"Shapes", NK_MINIMIZED, 0))
	{
		render_shape_tree();
		nk_tree_pop(g_nk_context);
	}
	if (nk_tree_push_id(g_nk_context, NK_TREE_TAB,
	"Lightsources", NK_MINIMIZED, 1))
	{
		render_lightsource_tree();
		nk_tree_pop(g_nk_context);
	}
	if (nk_tree_push_id(g_nk_context, NK_TREE_TAB,
	"Materials", NK_MINIMIZED, 2))
	{
		render_material_tree();
		nk_tree_pop(g_nk_context);
	}
	if (nk_tree_push_id(g_nk_context, NK_TREE_TAB,
	"Textures", NK_MINIMIZED, 2))
	{
		render_texture_tree();
		nk_tree_pop(g_nk_context);
	}
}

void		gui_render_scene_tree(void)
{
	if (nk_begin(g_nk_context, "Scene objects", nk_rect(TREE_X,
	TREE_Y, TREE_WIDTH, TREE_HEIGHT), g_nk_window_flags | NK_WINDOW_TITLE))
	{
		render_items();
	}
	nk_end(g_nk_context);
}

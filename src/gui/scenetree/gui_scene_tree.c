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

void	gui_render_scene_tree(void)
{
	static	void (*render_tree_func)(void) = NULL;

	if (nk_begin(g_nk_context, "Scene tree", nk_rect(TREE_X, TREE_Y, TREE_WIDTH,
		TREE_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(g_nk_context, 25, 3);
		if (nk_button_label(g_nk_context, render_tree_func == render_shape_tree ? "-Shapes-" : "Shapes"))
			render_tree_func = render_shape_tree;
		if (nk_button_label(g_nk_context, render_tree_func == render_lightsource_tree ? "-Lights-" : "Lights"))
			render_tree_func = render_lightsource_tree;
		if (nk_button_label(g_nk_context, render_tree_func == render_material_tree ? "-Materials-" : "Materials"))
			render_tree_func = render_material_tree;
		if (render_tree_func != NULL)
		{
			nk_layout_row_dynamic(g_nk_context, 25, 1);
			render_tree_func();
		}
	}
	nk_end(g_nk_context);
}

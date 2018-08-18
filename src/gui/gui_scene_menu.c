/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:34:37 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 17:34:39 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "renderer.h"

extern struct nk_image	g_gui_images[9];

static void				add_lightsource_treeitem(void)
{
	if (nk_tree_push(g_nk_context,
		NK_TREE_TAB, "Add Lightsource", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 75, 3);
		nk_image(g_nk_context, g_gui_images[6]);
		nk_image(g_nk_context, g_gui_images[7]);
		nk_image(g_nk_context, g_gui_images[8]);
		nk_layout_row_dynamic(g_nk_context, 20, 3);
		nk_label(g_nk_context, "Point", NK_TEXT_CENTERED);
		nk_label(g_nk_context, "Spot", NK_TEXT_CENTERED);
		nk_label(g_nk_context, "Directional", NK_TEXT_CENTERED);
		if (nk_button_label(g_nk_context, "Add"))
			gui_add_pointlightsource();
		if (nk_button_label(g_nk_context, "Add"))
			gui_add_spotlightsource();
		if (nk_button_label(g_nk_context, "Add"))
			gui_add_dirlightsource();
		nk_tree_pop(g_nk_context);
	}
}

static void				add_shapes_treeitem(void)
{
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Add Shape", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 75, 3);
		nk_image(g_nk_context, g_gui_images[0]);
		nk_image(g_nk_context, g_gui_images[4]);
		nk_image(g_nk_context, g_gui_images[2]);
		nk_layout_row_dynamic(g_nk_context, 20, 3);
		nk_label(g_nk_context, "Sphere", NK_TEXT_CENTERED);
		nk_label(g_nk_context, "Cone", NK_TEXT_CENTERED);
		nk_label(g_nk_context, "Cylinder", NK_TEXT_CENTERED);
		if (nk_button_label(g_nk_context, "Add"))
			gui_add_sphere();
		if (nk_button_label(g_nk_context, "Add"))
			gui_add_cone();
		if (nk_button_label(g_nk_context, "Add"))
			gui_add_cylinder();
		nk_layout_row_dynamic(g_nk_context, 75, 3);
		nk_image(g_nk_context, g_gui_images[5]);
		nk_layout_row_dynamic(g_nk_context, 20, 3);
		nk_label(g_nk_context, "Plane", NK_TEXT_CENTERED);
		nk_layout_row_dynamic(g_nk_context, 20, 3);
		if (nk_button_label(g_nk_context, "Add"))
			gui_add_plane();
		nk_tree_pop(g_nk_context);
	}
}

static void				add_material_treeitem(void)
{
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Add Material", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 20, 1);
		if (nk_button_label(g_nk_context, "Add material"))
			gui_add_material();
		nk_tree_pop(g_nk_context);
	}
}

static void				add_vfx_treeitem(void)
{
	static t_bool	vfx[RT_MAX_VFX] = {FALSE};

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Visual effects", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 20, 1);
		if (nk_checkbox_label(g_nk_context, "Black&White", &vfx[BW_ID]))
			vfx_toggle_bw();
		if (nk_checkbox_label(g_nk_context, "Sepia", &vfx[SEPIA_ID]))
			vfx_toggle_sepia();
		if (nk_checkbox_label(g_nk_context, "Blur", &vfx[BLUR_ID]))
			vfx_toggle_blur();
		if (nk_checkbox_label(g_nk_context, "Cartoon", &vfx[CARTOON_ID]))
			vfx_toggle_cartoon();
		nk_tree_pop(g_nk_context);
	}
}

void					gui_render_scene_menu(void)
{
	if (nk_begin(g_nk_context, "Scene", nk_rect(SCENEMENU_X, SCENEMENU_Y,
	SCENEMENU_WIDTH, SCENEMENU_HEIGHT), g_nk_window_flags | NK_WINDOW_TITLE))
	{
		if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Menu", NK_MAXIMIZED))
		{
			gui_choose_scene();
			nk_layout_row_dynamic(g_nk_context, 25, 1);
			if (nk_button_label(g_nk_context, "Take-a-Snapshot"))
				gui_screenshot();
			nk_tree_pop(g_nk_context);
		}
		add_vfx_treeitem();
		add_shapes_treeitem();
		add_lightsource_treeitem();
		add_material_treeitem();
	}
	nk_end(g_nk_context);
}

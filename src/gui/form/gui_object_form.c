/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_object_form.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

static const void		*g_selected_object = NULL;
static t_buff_target	g_selected_buff_target = NONE_TARGET;

void					gui_select_object(t_claddress addr, const t_buff_target target)
{
	g_main_scene.config.selected_shape_addr = NONE_SELECTED_ADDR;
	g_selected_buff_target = target;
	if (target == SHAPEBUFF_TARGET && addr != NONE_SELECTED_ADDR)
	{
		g_main_scene.config.selected_shape_addr = addr;
		g_selected_object = (const t_shape*)(g_main_scene.host_shapebuffer + addr);
	}
	else if (target == LIGHTSOURCEBUFF_TARGET)
		g_selected_object = (const t_lightsource*)(g_main_scene.host_lightsourcebuffer + addr);
	else if (target == MATERIALBUFF_TARGET)
		g_selected_object = (const t_material*)(g_main_scene.host_materialbuffer + addr);
	else if (target == TEXTUREBUFF_TARGET)
		g_selected_object = (const t_material*)(g_main_scene.host_texturebuffer + addr);
}

static const char		*obtain_caption(void)
{
	if (g_selected_buff_target == SHAPEBUFF_TARGET)
		return ("Object [Shape]");
	else if (g_selected_buff_target == LIGHTSOURCEBUFF_TARGET)
		return ("Object [Lightsource]");
	else if (g_selected_buff_target == MATERIALBUFF_TARGET)
		return ("Object [Material]");
	else if (g_selected_buff_target == TEXTUREBUFF_TARGET)
		return ("Object [Texture]");
	return ("Object");
}

void					gui_render_object(void)
{
	if (nk_begin(g_nk_context, obtain_caption(), nk_rect(OBJ_X, OBJ_Y, OBJ_WIDTH, OBJ_HEIGHT),
				g_nk_window_flags | NK_WINDOW_TITLE))
	{
		if (g_selected_buff_target == SHAPEBUFF_TARGET)
			render_shape_form((const t_shape*)g_selected_object);
		else if (g_selected_buff_target == LIGHTSOURCEBUFF_TARGET)
			render_lightsource_form((const t_lightsource*)g_selected_object);
		else if (g_selected_buff_target == MATERIALBUFF_TARGET)
			render_material_form((const t_material*)g_selected_object);
		else if (g_selected_buff_target == TEXTUREBUFF_TARGET)
			render_texture_form((const t_texture*)g_selected_object);
		else
		{
			nk_layout_row_dynamic(g_nk_context, 100, 1);
			nk_label(g_nk_context, "OBJECT IS NOT SELECTED", NK_TEXT_CENTERED);
		}
	}
	nk_end(g_nk_context);
}

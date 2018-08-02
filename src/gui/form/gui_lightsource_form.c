/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_lightsource_form.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static void	update_lightsource(const t_lightsource *old_lightsource,
const t_lightsource *new_lightsource)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_lightsource, new_lightsource, sizeof(t_lightsource)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, new_lightsource->addr,
	sizeof(t_lightsource), LIGHTSOURCEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_lightsource, 0, sizeof(t_lightsource));
	scenebuffer_unmap(&g_main_scene, LIGHTSOURCEBUFF_TARGET);
}

static void	render_actual_lightsource_form(const t_lightsource *lightsource)
{
	const t_byte	*actual;

	actual = lightsource_get_actual(lightsource);
	if (lightsource->lightsource_type == POINTLIGHT)
		render_pointlightsource_form(lightsource, (const t_pointlightsource*)actual);
	else if (lightsource->lightsource_type == DIRLIGHT)
		render_dirlightsource_form(lightsource, (const t_dirlightsource*)actual);
	else if (lightsource->lightsource_type == SPOTLIGHT)
		render_spotlightsource_form(lightsource, (const t_spotlightsource*)actual);
}

void		render_lightsource_form(const t_lightsource *lightsource)
{
	t_lightsource	new_lightsource;
	struct nk_color	light_color;
	float			intensity;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Lightsource", NK_MAXIMIZED))
	{
		new_lightsource = *lightsource;
		intensity = new_lightsource.intensity;
		light_color = to_nkcolor(new_lightsource.color);
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label_colored(g_nk_context, "color", NK_TEXT_LEFT, property_color);
		gui_render_color_picker(&light_color);
		nk_label_colored(g_nk_context, "intensity", NK_TEXT_LEFT, property_color);
		nk_property_float(g_nk_context, "#value", 0.0f, &intensity, 1.0f, 0.1f, 0.1f);
		new_lightsource.intensity = intensity;
		new_lightsource.color = from_nkcolor(light_color);
		update_lightsource(lightsource, &new_lightsource);
		nk_tree_pop(g_nk_context);
	}
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	render_actual_lightsource_form(lightsource);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_pointlightsource_form.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static void	update_pointlightsource(const t_lightsource *lightsource,
const t_pointlightsource *old_pointlightsrc,
const t_pointlightsource *new_pointlightsrc)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_pointlightsrc, new_pointlightsrc,
		sizeof(t_pointlightsource)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, lightsource->addr + sizeof(t_lightsource),
	sizeof(t_pointlightsource), LIGHTSOURCEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_pointlightsrc,
		0, sizeof(t_pointlightsource));
	scenebuffer_unmap(&g_main_scene, LIGHTSOURCEBUFF_TARGET);
}

static void	render_pointlightsource_attenuation(
	t_pointlightsource *pointlightsrc)
{
	float	c;
	float	l;
	float	q;

	c = pointlightsrc->attenuation.x;
	l = pointlightsrc->attenuation.y;
	q = pointlightsrc->attenuation.z;
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "attenuation", NK_TEXT_LEFT, property_color);
	nk_property_float(g_nk_context, "#c:", 0.01f, &c, INFINITY, 0.005f, 0.005f);
	nk_property_float(g_nk_context, "#l:", 0.0f, &l, INFINITY, 0.005f, 0.005f);
	nk_property_float(g_nk_context, "#q:", 0.0f, &q, INFINITY, 0.005f, 0.005f);
	pointlightsrc->attenuation.x = c;
	pointlightsrc->attenuation.y = l;
	pointlightsrc->attenuation.z = q;
}

void		render_pointlightsource_form(const t_lightsource *lightsource,
const t_pointlightsource *pointlightsrc)
{
	t_pointlightsource	new_pointlightsource;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB,
		"Point lightsource", NK_MAXIMIZED))
	{
		new_pointlightsource = *pointlightsrc;
		render_pointlightsource_attenuation(&new_pointlightsource);
		update_pointlightsource(lightsource,
			pointlightsrc, &new_pointlightsource);
		nk_tree_pop(g_nk_context);
	}
}

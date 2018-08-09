/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_spotlightsource_form.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static void	update_spotlightsource(const t_lightsource *lightsource,
const t_spotlightsource *old_spotlightsrc,
const t_spotlightsource *new_spotlightsrc)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_spotlightsrc, new_spotlightsrc, sizeof(t_spotlightsource)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, lightsource->addr + sizeof(t_lightsource),
	sizeof(t_spotlightsource), LIGHTSOURCEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_spotlightsrc, 0, sizeof(t_spotlightsource));
	scenebuffer_unmap(&g_main_scene, LIGHTSOURCEBUFF_TARGET);
}

static void	render_spotlightsource_attenuation(t_spotlightsource *spotlightsrc)
{
	float	c;
	float	l;
	float	q;

	c = spotlightsrc->attenuation.x;
	l = spotlightsrc->attenuation.y;
	q = spotlightsrc->attenuation.z;
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "attenuation", NK_TEXT_LEFT, property_color);
	nk_property_float(g_nk_context, "#c:", 0.01f, &c, INFINITY, 0.005f, 0.005f);
	nk_property_float(g_nk_context, "#l:", 0.0f, &l, INFINITY, 0.005f, 0.005f);
	nk_property_float(g_nk_context, "#q:", 0.0f, &q, INFINITY, 0.005f, 0.005f);
	spotlightsrc->attenuation.x = c;
	spotlightsrc->attenuation.y = l;
	spotlightsrc->attenuation.z = q;
}

static void	render_spotlightsource_direction(t_spotlightsource *spotlightsrc)
{
	t_vec3d	direction;

	direction = opencl_vec3_to_vec3(spotlightsrc->direction);
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "direction", NK_TEXT_LEFT, property_color);
	nk_property_double(g_nk_context, "#x:", -INFINITY, &direction.x, INFINITY, 0.1f, 0.1f);
	nk_property_double(g_nk_context, "#y:", -INFINITY, &direction.y, INFINITY, 0.1f, 0.1f);
	nk_property_double(g_nk_context, "#z:", -INFINITY, &direction.z, INFINITY, 0.1f, 0.1f);
	direction = vec3d_normalize(&direction);
	spotlightsrc->direction.x = direction.x;
	spotlightsrc->direction.y = direction.y;
	spotlightsrc->direction.z = direction.z;
}

void		render_spotlightsource_form(const t_lightsource *lightsource,
const t_spotlightsource *spotlightsrc)
{
	t_spotlightsource	new_spotlightsrc;
	float				angle;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Spot lightsource", NK_MAXIMIZED))
	{
		new_spotlightsrc = *spotlightsrc;
		angle = (180.0 / M_PI) * acos(new_spotlightsrc.cosangle);
		nk_label_colored(g_nk_context, "angle", NK_TEXT_LEFT, property_color);
		nk_property_float(g_nk_context, "#value", 1.0f,
			&angle, 89.0f, 1.0f, 1.0f);
		new_spotlightsrc.cosangle = cos(angle * M_PI / 180.0);
		render_spotlightsource_attenuation(&new_spotlightsrc);
		render_spotlightsource_direction(&new_spotlightsrc);
		update_spotlightsource(lightsource, spotlightsrc, &new_spotlightsrc);
		nk_tree_pop(g_nk_context);
	}
}

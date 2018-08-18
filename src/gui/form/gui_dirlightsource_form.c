/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_dirlightsource_form.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static void	update_dirlightsource(const t_lightsource *lightsource,
const t_dirlightsource *old_dirlightsrc,
const t_dirlightsource *new_dirlightsrc)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_dirlightsrc, new_dirlightsrc,
		sizeof(t_dirlightsource)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, lightsource->addr + sizeof(t_lightsource),
		sizeof(t_dirlightsource), LIGHTSOURCEBUFF_TARGET);
	scenebuffer_put(&g_main_scene, (void*)new_dirlightsrc,
		0, sizeof(t_dirlightsource));
	scenebuffer_unmap(&g_main_scene, LIGHTSOURCEBUFF_TARGET);
}

static void	render_dirlightsource_direction(t_dirlightsource *dirlightsrc)
{
	t_vec3d	direction;

	direction = opencl_vec3_to_vec3(dirlightsrc->direction);
	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label_colored(g_nk_context, "direction", NK_TEXT_LEFT, property_color);
	nk_property_double(g_nk_context, "#x:", -INFINITY,
		&direction.x, INFINITY, 0.1f, 0.1f);
	nk_property_double(g_nk_context, "#y:", -INFINITY,
		&direction.y, INFINITY, 0.1f, 0.1f);
	nk_property_double(g_nk_context, "#z:", -INFINITY,
		&direction.z, INFINITY, 0.1f, 0.1f);
	direction = vec3d_normalize(&direction);
	dirlightsrc->direction.x = direction.x;
	dirlightsrc->direction.y = direction.y;
	dirlightsrc->direction.z = direction.z;
}

void		render_dirlightsource_form(const t_lightsource *lightsource,
const t_dirlightsource *dirlightsrc)
{
	t_dirlightsource	new_dirlightsrc;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB,
		"Parallel lightsource", NK_MAXIMIZED))
	{
		new_dirlightsrc = *dirlightsrc;
		render_dirlightsource_direction(&new_dirlightsrc);
		update_dirlightsource(lightsource, dirlightsrc, &new_dirlightsrc);
		nk_tree_pop(g_nk_context);
	}
}

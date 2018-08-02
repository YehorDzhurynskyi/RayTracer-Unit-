/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_add_pointlightsource.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include "logger.h"

void	gui_add_pointlightsource(void)
{
	t_lightsource		lightsource;
	t_pointlightsource	pointlightsource;
	t_primitive			primitive;

	lightsource = scenebuffer_default_lightsource();
	pointlightsource = scenebuffer_default_pointlightsource();
	primitive = scenebuffer_default_primitive();
	primitive.primitive_type = POINT;
	lightsource.lightsource_type = POINTLIGHT;
	scenebuffer_map(&g_main_scene, g_main_scene.meta.lightsources_size,
	sizeof(t_lightsource) + sizeof(t_pointlightsource), LIGHTSOURCEBUFF_TARGET);
	scenebuffer_add_lightsource(&g_main_scene, &lightsource, &pointlightsource);
	// TODO: refactor primitive to shape
	scenebuffer_add_primitive(&g_main_scene, &primitive, NULL, LIGHTSOURCEBUFF_TARGET);
	scenebuffer_unmap(&g_main_scene, LIGHTSOURCEBUFF_TARGET);
	log_notify("Point lightsource was added to scene");
}

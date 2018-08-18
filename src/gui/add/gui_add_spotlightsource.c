/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_add_spotlightsource.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include "logger.h"

void	gui_add_spotlightsource(void)
{
	t_lightsource		lightsource;
	t_spotlightsource	spotlightsource;
	t_primitive			primitive;

	lightsource = scenebuffer_default_lightsource();
	spotlightsource = scenebuffer_default_spotlightsource();
	primitive = scenebuffer_default_primitive();
	primitive.primitive_type = POINT;
	lightsource.lightsource_type = SPOTLIGHT;
	scenebuffer_map(&g_main_scene, g_main_scene.meta.lightsources_size,
	sizeof(t_lightsource) + sizeof(t_spotlightsource), LIGHTSOURCEBUFF_TARGET);
	scenebuffer_add_lightsource(&g_main_scene, &lightsource, &spotlightsource);
	scenebuffer_add_primitive(&g_main_scene, &primitive, NULL,
		LIGHTSOURCEBUFF_TARGET);
	scenebuffer_unmap(&g_main_scene, LIGHTSOURCEBUFF_TARGET);
	log_notify("Spot lightsource was added to scene");
}

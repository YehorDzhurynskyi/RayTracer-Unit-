/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_add_dirlightsource.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include "logger.h"

void	gui_add_dirlightsource(void)
{
	t_lightsource		lightsource;
	t_dirlightsource	dirlightsource;

	lightsource = scenebuffer_default_lightsource();
	lightsource.lightsource_type = DIRLIGHT;
	dirlightsource = scenebuffer_default_dirlightsource();
	scenebuffer_map(&g_main_scene, g_main_scene.meta.lightsources_size,
	sizeof(t_lightsource) + sizeof(t_dirlightsource), LIGHTSOURCEBUFF_TARGET);
	scenebuffer_add_lightsource(&g_main_scene, &lightsource, &dirlightsource);
	scenebuffer_unmap(&g_main_scene, LIGHTSOURCEBUFF_TARGET);
	log_notify("Parallel lightsource was added to scene");
}

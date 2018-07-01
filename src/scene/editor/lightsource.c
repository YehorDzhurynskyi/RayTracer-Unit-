/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include <assert.h>

static inline size_t	lightsource_sizeof(t_lightsource_type type)
{
	if (type == DIRLIGHT)
		return (sizeof(t_dirlightsource));
	else if (type == POINTLIGHT)
		return (sizeof(t_pointlightsource));
	else if (type == SPOTLIGHT)
		return (sizeof(t_spotlightsource));
	assert(FALSE && "Light structure instance should have lighttype field");
	return (0);
}

void	scenebuffer_add_lightsource(t_scene *scene,
t_lightsource *lightsource, const void *actual_lightsource)
{
	lightsource->addr = scene->meta.lightsources_size;
	scenebuffer_append(scene, lightsource, sizeof(t_lightsource), LIGHTSOURCEBUFF_TARGET);
	scenebuffer_append(scene, actual_lightsource,
	lightsource_sizeof(lightsource->lightsource_type), LIGHTSOURCEBUFF_TARGET);
	scene->meta.nlightsources++;
}

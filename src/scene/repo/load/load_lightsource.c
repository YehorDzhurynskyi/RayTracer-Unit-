/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lightsources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

static void	load_actual_lightsource(t_scene *scene,
const t_cson *lightsrc_cson, t_lightsource *lightsrc)
{
	const void	*actual_lightsource;

	actual_lightsource = NULL;
	if (lightsrc->lightsource_type == DIRLIGHT)
		actual_lightsource = (t_dirlightsource[]){deserialize_dirlightsource(lightsrc_cson)};
	else if (lightsrc->lightsource_type == POINTLIGHT)
		actual_lightsource = (t_pointlightsource[]){deserialize_pointlightsource(lightsrc_cson)};
	else if (lightsrc->lightsource_type == SPOTLIGHT)
		actual_lightsource = (t_spotlightsource[]){deserialize_spotlightsource(lightsrc_cson)};
	scenebuffer_add_lightsource(scene, lightsrc, actual_lightsource);
}

void	load_lightsource(t_scene *scene, const t_cson *cson)
{
	t_lightsource	lightsource;
	const t_cson	*primitive_cson;

	lightsource = deserialize_lightsource(cson);
	load_actual_lightsource(scene, cson, &lightsource);
	if (lightsource.lightsource_type == SPOTLIGHT || lightsource.lightsource_type == POINTLIGHT)
	{
		primitive_cson = cson_valueof(cson, CSON_PRIMITIVE_KEY);
		if (primitive_cson != NULL)
			load_primitive(scene, primitive_cson, LIGHTSOURCEBUFF_TARGET);
	}
}

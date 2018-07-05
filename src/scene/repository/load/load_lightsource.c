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

#include "scenerepository.h"
#include "sceneeditor.h"
#include <assert.h>

static t_err_code	load_actual_lightsource(t_scene *scene,
const t_cson *lightsrc_cson, t_lightsource *lightsrc)
{
	t_err_code		err;
	const void		*actual_lightsource;

	err = RT_NO_ERROR;
	actual_lightsource = NULL;
	if (lightsrc->lightsource_type == DIRLIGHT)
		actual_lightsource = (t_dirlightsource[]){deserialize_dirlightsource(lightsrc_cson, &err)};
	else if (lightsrc->lightsource_type == POINTLIGHT)
		actual_lightsource = (t_pointlightsource[]){deserialize_pointlightsource(lightsrc_cson, &err)};
	else if (lightsrc->lightsource_type == SPOTLIGHT)
		actual_lightsource = (t_spotlightsource[]){deserialize_spotlightsource(lightsrc_cson, &err)};
	else
		return (RT_WRONG_VALUE_TYPE_ERROR);
	scenebuffer_add_lightsource(scene, lightsrc, actual_lightsource);
	return (err);
}

t_err_code	load_lightsource(t_scene *scene, const t_cson *cson)
{
	t_err_code		err;
	t_lightsource	lightsource;
	const t_cson	*primitive_cson;

	err = RT_NO_ERROR;
	if (cson == NULL)
		return (RT_VALUE_PARSING_ERROR);
	if (cson_is_object(cson) == FALSE)
		return (RT_WRONG_VALUE_FORMAT_ERROR);
	lightsource = deserialize_lightsource(cson, &err);
	load_actual_lightsource(scene, cson, &lightsource);
	primitive_cson = cson_valueof(cson, CSON_PRIMITIVE_KEY);
	if (primitive_cson != NULL)
		load_primitive(scene, primitive_cson, LIGHTSOURCEBUFF_TARGET);
	return (err);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_pointlightsource.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

t_pointlightsource	deserialize_pointlightsource(const t_cson *cson)
{
	t_pointlightsource	pointlightsource;

	pointlightsource.position = deserialize_vec3_required(cson_valueof(cson, CSON_POSITION_KEY), FALSE);
	pointlightsource.attenuation = deserialize_vec3_optional(cson_valueof(cson, CSON_ATTENUATION_KEY), FALSE,
	(t_vec3d){1.0, 0.0, 0.0});
	return (pointlightsource);
}

t_cson			*serialize_pointlight(const t_pointlightsource *pointlightsource)
{
	t_cson		*cson;
	t_clvec3	position;
	t_clvec3	attenuation;

	cson = cson_object();
	position = pointlightsource->position;
	attenuation = pointlightsource->attenuation;
	cson_put(cson, CSON_POSITION_KEY, serialize_vec3(&position));
	cson_put(cson, CSON_ATTENUATION_KEY, serialize_vec3(&attenuation));
	return (cson);
}

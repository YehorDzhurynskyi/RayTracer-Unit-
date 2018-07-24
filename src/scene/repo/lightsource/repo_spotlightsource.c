/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_spotlightsource.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include <math.h>

t_spotlightsource	deserialize_spotlightsource(const t_cson *cson)
{
	t_spotlightsource		spotlightsource;

	spotlightsource.position = deserialize_vec3_required(cson_valueof(cson, CSON_POSITION_KEY), FALSE);
	spotlightsource.direction = deserialize_vec3_required(cson_valueof(cson, CSON_DIRECTION_KEY), TRUE);
	spotlightsource.attenuation = deserialize_vec3_optional(cson_valueof(cson, CSON_ATTENUATION_KEY), FALSE,
	(t_vec3d){1.0, 0.0, 0.0});
	spotlightsource.cosangle = deserialize_real_required(cson_valueof(cson, CSON_ANGLE_KEY));
	spotlightsource.cosangle = cos(spotlightsource.cosangle * M_PI / 180.0);
	return (spotlightsource);
}

t_cson		*serialize_spotlightsource(const t_spotlightsource *spotlightsource)
{
	t_cson		*cson;
	t_clvec3	direction;
	t_clvec3	position;
	t_clvec3	attenuation;

	cson = cson_object();
	direction = spotlightsource->direction;
	position = spotlightsource->position;
	attenuation = spotlightsource->attenuation;
	cson_put(cson, CSON_DIRECTION_KEY, serialize_vec3(&direction));
	cson_put(cson, CSON_POSITION_KEY, serialize_vec3(&position));
	cson_put(cson, CSON_ATTENUATION_KEY, serialize_vec3(&attenuation));
	cson_put_real(cson, CSON_ANGLE_KEY, (180.0 / M_PI)
	* acos(spotlightsource->cosangle));
	return (cson);
}

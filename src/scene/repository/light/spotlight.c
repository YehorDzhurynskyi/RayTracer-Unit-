/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
#include <math.h>

t_spotlight	deserialize_spotlight(const t_cson *cson)
{
	t_spotlight	spotlight;

	spotlight.position = deserialize_vec4(cson_valueof(cson,
	CSON_POSITION_KEY), FALSE);
	spotlight.attenuation = deserialize_vec4(cson_valueof(cson,
	CSON_ATTENUATION_KEY), FALSE);
	spotlight.direction = deserialize_vec4(cson_valueof(cson,
	CSON_DIRECTION_KEY), TRUE);
	spotlight.cosangle = cson_get_default_real(cson_valueof(cson,
	CSON_ANGLE_KEY), 20.0);
	spotlight.cosangle = cos(spotlight.cosangle * M_PI / 180.0);
	return (spotlight);
}

t_cson		*serialize_spotlight(const t_spotlight *spotlight)
{
	t_cson		*cson;
	t_clvec4	direction;
	t_clvec4	position;
	t_clvec4	attenuation;

	cson = cson_object();
	direction = spotlight->direction;
	position = spotlight->position;
	attenuation = spotlight->attenuation;
	cson_put(cson, CSON_DIRECTION_KEY, serialize_vec4(&direction));
	cson_put(cson, CSON_POSITION_KEY, serialize_vec4(&position));
	cson_put(cson, CSON_ATTENUATION_KEY, serialize_vec4(&attenuation));
	cson_put_real(cson, CSON_ANGLE_KEY, (180.0 / M_PI)
	* acos(spotlight->cosangle));
	return (cson);
}

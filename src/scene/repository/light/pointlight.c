/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"

t_pointlight	deserialize_pointlight(const t_cson *cson)
{
	t_pointlight	pointlight;

	pointlight.position = deserialize_vec4(cson_valueof(cson,
	CSON_POSITION_KEY), FALSE);
	pointlight.attenuation = deserialize_vec4(cson_valueof(cson,
	CSON_ATTENUATION_KEY), FALSE);
	return (pointlight);
}

t_cson			*serialize_pointlight(const t_pointlight *pointlight)
{
	t_cson		*cson;
	t_clvec4	position;
	t_clvec4	attenuation;

	cson = cson_object();
	position = pointlight->position;
	attenuation = pointlight->attenuation;
	cson_put(cson, CSON_POSITION_KEY, serialize_vec4(&position));
	cson_put(cson, CSON_ATTENUATION_KEY, serialize_vec4(&attenuation));
	return (cson);
}

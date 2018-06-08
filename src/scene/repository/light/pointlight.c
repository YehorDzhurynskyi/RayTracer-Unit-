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
#include "logger.h"

t_pointlight	deserialize_pointlight(const t_cson *cson, t_err_code *err)
{
	t_pointlight	pointlight;
	const t_cson	*position_cson;
	const t_cson	*attenuation_cson;

	position_cson = cson_valueof(cson, CSON_POSITION_KEY);
	if (position_cson == NULL)
	{
		*err = RT_NO_REQUIRED_VALUE_ERROR;
		log_error("Pointlight's position vector is absent", *err);
		return ((t_pointlight){});
	}
	pointlight.position = deserialize_vec4(position_cson, FALSE, err);
	attenuation_cson = cson_valueof(cson, CSON_ATTENUATION_KEY);
	if (attenuation_cson == NULL || cson_is_array(attenuation_cson) == FALSE
	|| cson_size(attenuation_cson) != 3)
	{
		log_notify("Attenuation is absent or is not vector3-type"
		" value, the value is set to [1, 0, 0] by default");
		pointlight.attenuation = (t_clvec4){{1.0f, 0.0f, 0.0f, 0.0f}};
	}
	else
		pointlight.attenuation = deserialize_vec4(attenuation_cson, FALSE, err);
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

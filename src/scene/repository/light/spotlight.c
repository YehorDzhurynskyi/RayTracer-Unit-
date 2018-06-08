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
#include "logger.h"

#define SPOT_ANGLE		20.0
#define SPOT_ANGLE_STR	TO_STRING(SPOT_ANGLE)

t_spotlight	deserialize_spotlight(const t_cson *cson, t_err_code *err)
{
	t_spotlight		spotlight;
	const t_cson	*position_cson;
	const t_cson	*attenuation_cson;
	const t_cson	*direction_cson;
	const t_cson	*angle_cson;

	position_cson = cson_valueof(cson, CSON_POSITION_KEY);
	direction_cson = cson_valueof(cson, CSON_DIRECTION_KEY);
	if (position_cson == NULL || direction_cson == NULL)
	{
		*err = RT_NO_REQUIRED_VALUE_ERROR;
		if (position_cson == NULL)
			log_error("Spotlight's position vector is absent", *err);
		if (direction_cson == NULL)
			log_error("Spotlight's direction vector is absent", *err);
		return ((t_spotlight){});
	}
	spotlight.position = deserialize_vec4(position_cson, FALSE, err);
	spotlight.direction = deserialize_vec4(direction_cson, TRUE, err);
	attenuation_cson = cson_valueof(cson, CSON_ATTENUATION_KEY);
	if (attenuation_cson == NULL || cson_is_array(attenuation_cson) == FALSE
	|| cson_size(attenuation_cson) != 3)
	{
		log_notify("Attenuation is absent or is not vector3-type"
		" value, the value is set to [1, 0, 0] by default");
		spotlight.attenuation = (t_clvec4){{1.0f, 0.0f, 0.0f, 0.0f}};
	}
	else
		spotlight.attenuation = deserialize_vec4(attenuation_cson, FALSE, err);
	angle_cson = cson_valueof(cson, CSON_ANGLE_KEY);
	if (angle_cson == NULL || cson_is_real(angle_cson) == FALSE)
	{
		log_notify("Spot light angle is absent or is not real-type"
		" value, the value is set to " SPOT_ANGLE_STR " by default");
		spotlight.cosangle = SPOT_ANGLE;
	}
	else
		spotlight.cosangle = cson_get_real(angle_cson);
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

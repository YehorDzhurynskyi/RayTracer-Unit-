/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
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

#define ANGLE		15.0
#define ANGLE_STR	TO_STRING(ANGLE)

t_cone	deserialize_cone(const t_cson *cson, t_err_code *err)
{
	t_cone			cone;
	const t_cson	*direction_cson;
	const t_cson	*angle_cson;

	direction_cson = cson_valueof(cson, CSON_DIRECTION_KEY);
	if (direction_cson == NULL)
	{
		*err = RT_NO_REQUIRED_VALUE_ERROR;
		log_error("Cone's diretion vector is absent", *err);
		return ((t_cone){});
	}
	cone.direction = deserialize_vec4(direction_cson, TRUE, err);
	angle_cson = cson_valueof(cson, CSON_ANGLE_KEY);
	if (angle_cson == NULL || cson_is_real(angle_cson) == FALSE)
	{
		log_notify("Cone angle is absent or is not real-type"
		" value, the value is set to " ANGLE_STR " by default");
		cone.cos2angle = ANGLE;
	}
	else
		cone.cos2angle = cson_get_real(angle_cson);
	cone.cos2angle = cos(cone.cos2angle * M_PI / 180.0);
	cone.cos2angle *= cone.cos2angle;
	return (cone);
}

t_cson	*serialize_cone(const t_cone *cone)
{
	t_cson		*cson;
	t_clvec4	direction;

	cson = cson_object();
	direction = cone->direction;
	cson_put(cson, CSON_DIRECTION_KEY, serialize_vec4(&direction));
	cson_put_real(cson, CSON_ANGLE_KEY,
	(180.0 / M_PI) * acos(sqrt(cone->cos2angle)));
	return (cson);
}

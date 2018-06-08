/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
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

#define RADIUS		1.0
#define RADIUS_STR	TO_STRING(RADIUS)

t_cylinder	deserialize_cylinder(const t_cson *cson, t_err_code *err)
{
	t_cylinder		cylinder;
	const t_cson	*direction_cson;
	const t_cson	*radius_cson;

	direction_cson = cson_valueof(cson, CSON_DIRECTION_KEY);
	if (direction_cson == NULL)
	{
		*err = RT_NO_REQUIRED_VALUE_ERROR;
		log_error("Cylinder's diretion vector is absent", *err);
		return ((t_cylinder){});
	}
	cylinder.direction = deserialize_vec4(direction_cson, TRUE, err);
	radius_cson = cson_valueof(cson, CSON_RADIUS_KEY);
	if (radius_cson == NULL || cson_is_real(radius_cson))
	{
		log_notify("Cylinder radius is absent or is not real-type"
		" value, the value is set to " RADIUS_STR " by default");
		cylinder.radius2 = RADIUS;
	}
	else
		cylinder.radius2 = cson_get_real(radius_cson);
	cylinder.radius2 *= cylinder.radius2;
	return (cylinder);
}

t_cson		*serialize_cylinder(const t_cylinder *cylinder)
{
	t_cson		*cson;
	t_clvec4	direction;

	cson = cson_object();
	direction = cylinder->direction;
	cson_put(cson, CSON_DIRECTION_KEY, serialize_vec4(&direction));
	cson_put_real(cson, CSON_RADIUS_KEY, sqrt(cylinder->radius2));
	return (cson);
}

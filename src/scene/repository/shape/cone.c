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

t_cone	deserialize_cone(const t_cson *cson)
{
	t_cone	cone;

	cone.direction = deserialize_vec4(cson_valueof(cson, CSON_DIRECTION_KEY), TRUE);
	cone.cos2angle = cson_get_default_real(cson_valueof(cson, CSON_ANGLE_KEY), 15.0);
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

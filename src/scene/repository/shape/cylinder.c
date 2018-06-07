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

t_cylinder	deserialize_cylinder(const t_cson *cson)
{
	t_cylinder	cylinder;

	cylinder.direction = deserialize_vec4(cson_valueof(cson, CSON_DIRECTION_KEY), TRUE);
	cylinder.radius2 = cson_get_default_real(cson_valueof(cson, CSON_RADIUS_KEY), 1.0);
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

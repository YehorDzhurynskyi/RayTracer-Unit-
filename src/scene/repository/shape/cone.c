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
	t_cone	cone;

	(void)err;
	cone.cos2angle = deserialize_real(cson, CSON_ANGLE_KEY, ANGLE, ANGLE_STR);
	cone.cos2angle = cos(cone.cos2angle * M_PI / 180.0);
	cone.cos2angle *= cone.cos2angle;
	return (cone);
}

t_cson	*serialize_cone(const t_cone *cone)
{
	t_cson		*cson;

	cson = cson_object();
	cson_put_real(cson, CSON_ANGLE_KEY,
	(180.0 / M_PI) * acos(sqrt(cone->cos2angle)));
	return (cson);
}

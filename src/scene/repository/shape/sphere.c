/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
#include <math.h>

t_sphere	deserialize_sphere(const t_cson *cson)
{
	t_sphere	sphere;

	sphere.radius2 = cson_get_default_real(cson_valueof(cson, CSON_RADIUS_KEY), 1.0);
	return (sphere);
}

t_cson		*serialize_sphere(const t_sphere *sphere)
{
	t_cson	*cson;

	cson = cson_object();
	cson_put_real(cson, CSON_RADIUS_KEY, sqrt(sphere->radius2));
	return (cson);
}

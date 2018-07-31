/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "sceneiterator.h"
#include <math.h>

t_bool	sphere_intersected(const t_primitive *primitive, const t_ray *ray, float *t)
{
	const t_sphere	*sphere;
	t_vec3d			to_orig;
	t_vec3d			position;
	float			b;
	float			d;

	position = opencl_vec4_to_vec3(primitive->position);
	sphere = (const t_sphere*)primitive_get_actual(primitive);
	to_orig = vec3d_sub(&ray->origin, &position);
	b = vec3d_dot(&ray->direction, &to_orig);
	d = b * b - (vec3d_dot(&to_orig, &to_orig) - sphere->radius2);
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	return (limit(primitive, ray, t, -b - d)
	|| limit(primitive, ray, t, -b + d));
}

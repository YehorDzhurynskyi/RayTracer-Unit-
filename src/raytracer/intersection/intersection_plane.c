/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static t_vec3d	plane_get_normal(const t_primitive *primitive)
{
	return ((t_vec3d){primitive->orientation.s4, primitive->orientation.s5, primitive->orientation.s6});
}

t_bool			plane_intersected(const t_primitive *primitive, const t_ray *ray, float *t)
{
	t_vec3d	plane_normal;
	t_vec3d	to_plane;
	t_vec3d	position;
	float	denom;
	float	sign;

	position = opencl_vec4_to_vec3(primitive->position);
	plane_normal = plane_get_normal(primitive);
	denom = -vec3d_dot(&ray->direction, &plane_normal);
	sign = 1.0f;
	if (denom < 0.0f)
	{
		denom = -denom;
		sign = -sign;
	}
	if (denom > 1e-6)
	{
		to_plane = vec3d_sub(&ray->origin, &position);
		*t = sign * vec3d_dot(&to_plane, &plane_normal);
		*t /= denom;
		return (limit(primitive, ray, t, *t));
	}
	return (FALSE);
}

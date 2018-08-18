/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "sceneiterator.h"

static t_vec3d			cone_get_direction(const t_primitive *primitive)
{
	return ((t_vec3d){-primitive->orientation.s4,
	-primitive->orientation.s5, -primitive->orientation.s6});
}

inline static t_bool	is_cutted_cone(const t_primitive *primitive,
const t_ray *ray, float t)
{
	t_vec3d	cone_direction;
	t_vec3d	point;
	t_vec3d	position;

	position = opencl_vec3_to_vec3(primitive->position);
	point = vec3d_scalar(&ray->direction, t);
	point = vec3d_add(&point, &ray->origin);
	point = vec3d_sub(&point, &position);
	cone_direction = cone_get_direction(primitive);
	return (vec3d_dot(&point, &cone_direction) <= 0.0);
}

inline static int		find_scalar(const t_primitive *primitive,
const t_ray *ray, float *t1, float *t2)
{
	int	nroots;

	nroots = 0;
	if (limit(primitive, ray, t1, *t1) && !is_cutted_cone(primitive, ray, *t1))
	{
		++nroots;
	}
	if (limit(primitive, ray, t2, *t2) && !is_cutted_cone(primitive, ray, *t2))
	{
		if (nroots == 0)
			*t1 = *t2;
		++nroots;
	}
	if (nroots == 0)
		return (0);
	if (nroots == 2)
	{
		*t1 = *t1 < *t2 ? *t1 : *t2;
		*t2 = *t1 >= *t2 ? *t1 : *t2;
	}
	return (nroots);
}

int						cone_intersected(const t_primitive *primitive,
const t_ray *ray, float *t1, float *t2)
{
	float	abcd[4];
	t_vec3d	cone_direction;
	t_vec3d	position;
	t_vec3d	to_orig;

	cone_direction = cone_get_direction(primitive);
	position = opencl_vec4_to_vec3(primitive->position);
	to_orig = vec3d_sub(&ray->origin, &position);
	abcd[0] = vec3d_dot(&ray->direction, &cone_direction);
	abcd[2] = vec3d_dot(&to_orig, &cone_direction);
	abcd[1] = abcd[0] * abcd[2] - vec3d_dot(&ray->direction, &to_orig)
	* ((const t_cone*)primitive_get_actual(primitive))->cos2angle;
	abcd[0] = abcd[0] * abcd[0]
	- ((const t_cone*)primitive_get_actual(primitive))->cos2angle;
	abcd[2] = abcd[2] * abcd[2] - vec3d_dot(&to_orig, &to_orig)
	* ((const t_cone*)primitive_get_actual(primitive))->cos2angle;
	abcd[3] = abcd[1] * abcd[1] - abcd[0] * abcd[2];
	if (abcd[3] < 0.0)
		return (FALSE);
	abcd[3] = sqrt(abcd[3]);
	*t1 = (-abcd[1] - abcd[3]) / abcd[0];
	*t2 = (-abcd[1] + abcd[3]) / abcd[0];
	return (find_scalar(primitive, ray, t1, t2));
}

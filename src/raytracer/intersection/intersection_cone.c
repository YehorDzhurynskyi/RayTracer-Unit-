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

inline static t_bool	is_cutted_cone(const t_primitive *primitive, const t_ray *ray, float t)
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

inline static float		find_scalar(const t_primitive *primitive, const t_ray *ray,
const float t1, const float t2)
{
	t_bool	t1_intersect;
	t_bool	t2_intersect;
	float	target_t;

	t1_intersect = TRUE;
	t2_intersect = TRUE;
	if (!limit(primitive, ray, &target_t, t1) || is_cutted_cone(primitive, ray, t1))
		t1_intersect = FALSE;
	if (!limit(primitive, ray, &target_t, t2) || is_cutted_cone(primitive, ray, t2))
		t2_intersect = FALSE;
	if (!t1_intersect && !t2_intersect)
		return (-1.0f);
	if (t1_intersect && t2_intersect)
		target_t = t1 < t2 ? t1 : t2;
	else if (t1_intersect)
		target_t = t1_intersect ? t1 : t2;
	return (target_t);
}

t_bool					cone_intersected(const t_primitive *primitive, const t_ray *ray, float *t)
{
	float	a;
	float	b;
	float	c;
	float	d;
	t_vec3d	cone_direction;
	t_vec3d	position;
	t_vec3d	to_orig;

	cone_direction = cone_get_direction(primitive);
	position = opencl_vec4_to_vec3(primitive->position);
	to_orig = vec3d_sub(&ray->origin, &position);
	a = vec3d_dot(&ray->direction, &cone_direction);
	c = vec3d_dot(&to_orig, &cone_direction);
	b = a * c - vec3d_dot(&ray->direction, &to_orig) * ((const t_cone*)primitive_get_actual(primitive))->cos2angle;
	a = a * a - ((const t_cone*)primitive_get_actual(primitive))->cos2angle;
	c = c * c - vec3d_dot(&to_orig, &to_orig) * ((const t_cone*)primitive_get_actual(primitive))->cos2angle;
	d = b * b - a * c;
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	*t = find_scalar(primitive, ray, (-b - d) / a, (-b + d) / a);
	return (*t > 0.0f);
}

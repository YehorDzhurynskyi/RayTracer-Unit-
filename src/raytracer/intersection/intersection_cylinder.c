/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
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

static t_vec3d	cylinder_get_direction(const t_primitive *primitive)
{
	return ((t_vec3d){-primitive->orientation.s4,
	-primitive->orientation.s5, -primitive->orientation.s6});
}

static t_vec3d	calc_va(const t_primitive *primitive, const t_ray *ray)
{
	t_vec3d	position;
	t_vec3d	to_orig;
	t_vec3d	cylinder_direction;

	position = opencl_vec4_to_vec3(primitive->position);
	to_orig = vec3d_sub(&ray->origin, &position);
	cylinder_direction = cylinder_get_direction(primitive);
	return (vec3d_cross(&to_orig, &cylinder_direction));
}

static t_vec3d	calc_vb(const t_primitive *primitive, const t_ray *ray)
{
	t_vec3d	cylinder_direction;

	cylinder_direction = cylinder_get_direction(primitive);
	return (vec3d_cross(&ray->direction, &cylinder_direction));
}

static int		number_of_roots(t_bool t1_intersected, t_bool t2_intersected,
float *t1, float *t2)
{
	int	nroots;

	nroots = 0;
	if (t1_intersected)
		++nroots;
	if (t2_intersected)
	{
		if (nroots == 0)
			*t1 = *t2;
		++nroots;
	}
	return (nroots);
}

int				cylinder_intersected(const t_primitive *primitive,
const t_ray *ray, float *t1, float *t2)
{
	t_vec3d	va;
	t_vec3d	vb;
	float	a;
	float	b;
	float	d;

	va = calc_va(primitive, ray);
	vb = calc_vb(primitive, ray);
	a = vec3d_dot(&vb, &vb);
	b = vec3d_dot(&vb, &va);
	d = b * b - a * (vec3d_dot(&va, &va)
	- ((const t_cylinder*)primitive_get_actual(primitive))->radius2);
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	return (number_of_roots(limit(primitive, ray, t1, (-b - d) / a),
	limit(primitive, ray, t2, (-b + d) / a), t1, t2));
}

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

#include "intersection.h"
#include "sceneiterator.h"
#include <math.h>

static t_vec3d	cylinder_get_direction(const t_primitive *primitive)
{
	return ((t_vec3d){-primitive->orientation.s4, -primitive->orientation.s5, -primitive->orientation.s6});
}

t_bool			cylinder_intersected(const t_primitive *primitive, const t_ray *ray, float *t)
{
	const t_cylinder	*cylinder;
	t_vec3d				cylinder_direction;
	t_vec3d				position;
	t_vec3d				to_orig;
	t_vec3d				va;
	t_vec3d				vb;
	float				a;
	float				b;
	float				d;

	cylinder = (const t_cylinder*)primitive_get_actual(primitive);
	cylinder_direction = cylinder_get_direction(primitive);
	position = opencl_vec4_to_vec3(primitive->position);
	to_orig = vec3d_sub(&ray->origin, &position);
	va = vec3d_cross(&to_orig, &cylinder_direction);
	vb = vec3d_cross(&ray->direction, &cylinder_direction);
	a = vec3d_dot(&vb, &vb);
	b = vec3d_dot(&vb, &va);
	d = b * b - a * (vec3d_dot(&va, &va) - cylinder->radius2);
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	*t = (-b - d) / a;
	if (*t < 0.0)
		*t = (-b + d) / a;
	return (TRUE);
}
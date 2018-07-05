/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
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

const t_shape	*cast_ray(const t_scene *scene, const t_ray *ray, float *nearest_t)
{
	const t_shape	*nearest_shape;
	const t_shape	*shape;
	float			t;
	t_iterator		shape_iter;

	nearest_shape = NULL;
	*nearest_t = INFINITY;
	shape_iter = shape_begin(scene);
	while (has_next(&shape_iter))
	{
		shape = shape_next(&shape_iter);
		if (TRUE == shape_intersected(shape, ray, &t) && t > 1.0E-5 && t < *nearest_t)
		{
			*nearest_t = t;
			nearest_shape = shape;
		}
	}
	return (nearest_shape);
}

t_bool			shape_intersected(const t_shape *shape, const t_ray *ray, float *t)
{
	// TODO: shape could be a composite so in this case need to handle relation types etc
	const t_primitive *primitive;

	primitive = shape_get_primitive(shape);
	return (primitive_intersected(primitive, ray, t));
}

t_bool			primitive_intersected(const t_primitive *primitive, const t_ray *ray, float *t)
{
	t_bool prim_intersected = FALSE;
	if (primitive->primitive_type == SPHERE)
		prim_intersected = sphere_intersected(primitive, ray, t);
	else if (primitive->primitive_type == PLANE)
		prim_intersected = plane_intersected(primitive, ray, t);
	else if (primitive->primitive_type == CONE)
		prim_intersected = cone_intersected(primitive, ray, t);
	else if (primitive->primitive_type == CYLINDER)
		prim_intersected = cylinder_intersected(primitive, ray, t);
	else if (primitive->primitive_type == COMPOSITE || primitive->primitive_type == POINT) // TODO: making an assumption that the point is infinitely small
		return (FALSE);
	return (prim_intersected);
}

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

const t_shape			*cast_ray(const t_scene *scene,
const t_ray *ray, float *nearest_t)
{
	const t_shape	*nearest_shape;
	const t_shape	*shape;
	const t_shape	*intersected_shape;
	float			t;
	t_iterator		shape_iter;

	nearest_shape = NULL;
	*nearest_t = INFINITY;
	shape_iter = shape_begin(scene);
	while (has_next(&shape_iter))
	{
		shape = shape_next(&shape_iter);
		if ((intersected_shape = shape_intersected(shape, ray, &t)) != NULL
		&& t > 1.0E-5 && t < *nearest_t)
		{
			*nearest_t = t;
			nearest_shape = intersected_shape;
		}
	}
	return (nearest_shape);
}

static const t_shape	*union_intersected_shape(const t_shape *shape,
const t_ray *ray, float t_values[4])
{
	const t_shape	*nearest_union_shape;
	const t_shape	*child;
	t_iterator		union_children_iter;
	float			t1;
	float			t2;

	union_children_iter = children_begin(shape);
	nearest_union_shape = NULL;
	t_values[0] = INFINITY;
	t_values[1] = INFINITY;
	while (has_next(&union_children_iter))
	{
		child = children_next(&union_children_iter);
		if (child->relation_type != UNION)
			continue;
		if (primitive_intersected(child, ray, &t1, &t2) == 0)
			continue;
		if (t1 > 1.0E-5 && t1 < t_values[0])
		{
			nearest_union_shape = child;
			t_values[0] = t1;
			t_values[1] = t2;
		}
	}
	return (nearest_union_shape);
}

static const t_shape	*negation_intersected_shape(const t_shape *shape,
const t_ray *ray, float t_values[4])
{
	const t_shape	*nearest_negation_shape;
	const t_shape	*child;
	t_iterator		negation_children_iter;
	float			t1;
	float			t2;

	negation_children_iter = children_begin(shape);
	nearest_negation_shape = NULL;
	t_values[2] = INFINITY;
	t_values[3] = INFINITY;
	while (has_next(&negation_children_iter))
	{
		child = children_next(&negation_children_iter);
		if (child->relation_type != NEGATION ||
		primitive_intersected(child, ray, &t1, &t2) < 2 || t1 > t_values[0]
		|| (t1 < t_values[0] && t2 < t_values[0]))
			continue;
		if (t1 > 1.0E-5 && t2 > 1.0E-5 && t1 < t_values[2] && t2 < t_values[3])
		{
			t_values[2] = t1;
			t_values[3] = t2;
			nearest_negation_shape = child;
		}
	}
	return (nearest_negation_shape);
}

const t_shape			*shape_intersected(const t_shape *shape,
const t_ray *ray, float *t)
{
	const t_shape	*nearest_union_shape;
	const t_shape	*nearest_negation_shape;
	float			t_values[4];
	t_bool			shape_is_negated;

	if (shape->relation_type == NEGATION)
		return (NULL);
	if (shape->nchildren == 0)
		return (0 != primitive_intersected(shape, ray, t, NULL) ? shape : NULL);
	nearest_union_shape = union_intersected_shape(shape, ray, t_values);
	if (nearest_union_shape == NULL)
		return (NULL);
	nearest_negation_shape = negation_intersected_shape(shape, ray, t_values);
	if (nearest_negation_shape == NULL)
	{
		*t = t_values[0];
		return (nearest_union_shape);
	}
	if (t_values[2] < t_values[0] && t_values[1] < t_values[3])
		return (NULL);
	shape_is_negated = t_values[2] <= t_values[0]
	&& t_values[0] <= t_values[3] && t_values[3] <= t_values[1];
	*t = shape_is_negated ? t_values[3] : t_values[0];
	return (shape_is_negated ? nearest_negation_shape : nearest_union_shape);
}

int						primitive_intersected(const t_shape *shape,
const t_ray *ray, float *t1, float *t2)
{
	const t_primitive	*primitive;
	float				*pt1;
	float				*pt2;
	float				dummy_t1;
	float				dummy_t2;

	pt1 = t1;
	pt2 = t2;
	primitive = shape_get_primitive(shape);
	if (t1 == NULL)
		pt1 = &dummy_t1;
	if (t2 == NULL)
		pt2 = &dummy_t2;
	if (primitive->primitive_type == SPHERE)
		return (sphere_intersected(primitive, ray, pt1, pt2));
	else if (primitive->primitive_type == PLANE)
		return (plane_intersected(primitive, ray, pt1));
	else if (primitive->primitive_type == CONE)
		return (cone_intersected(primitive, ray, pt1, pt2));
	else if (primitive->primitive_type == CYLINDER)
		return (cylinder_intersected(primitive, ray, pt1, pt2));
	return (0);
}

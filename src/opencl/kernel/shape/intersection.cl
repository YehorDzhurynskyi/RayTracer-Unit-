/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static __constant t_shape	*union_intersected_shape(__constant t_shape *shape, const t_ray *ray,
t_scalar *union_t1, t_scalar *union_t2)
{
	t_iterator			union_children_iter = children_begin(shape);
	__constant t_shape	*nearest_union_shape = NULL;

	*union_t1 = INFINITY;
	*union_t2 = INFINITY;
	while (has_next(&union_children_iter))
	{
		__constant t_shape	*child = children_next(&union_children_iter);
		if (child->relation_type != UNION)
			continue;
		// t1 is always less then t2
		t_scalar	t1, t2;
		int nintersected_points = primitive_intersected(child, ray, &t1, &t2);
		if (nintersected_points == 0)
			continue;
		if (nintersected_points == 1 && t1 < 1.0E-5)
			continue;
		if (nintersected_points == 2 && t1 < 1.0E-5 && t2 < 1.0E-5)
			continue;
		if (nintersected_points == 1)
		{
			if (t1 > 1.0E-5 && t1 < *union_t1)
			{
				nearest_union_shape = child;
				*union_t1 = t1;
				*union_t2 = t1;
			}
		}
		else if (nintersected_points == 2)
		{
			if (t1 < 1.0E-5 && t2 > 1.0E-5 && t2 < *union_t1)
			{
				nearest_union_shape = child;
				*union_t1 = t2;
				*union_t2 = t2;
			}
			else if (t1 > 1.0E-5 && t1 < *union_t1)
			{
				nearest_union_shape = child;
				*union_t1 = t1;
				*union_t2 = t2;
			}
		}
	}
	return (nearest_union_shape);
}

static __constant t_shape	*negation_intersected_shape(__constant t_shape *shape, const t_ray *ray,
const t_scalar union_t1, const t_scalar union_t2, t_scalar *negation_t1, t_scalar *negation_t2)
{
	t_iterator	negation_children_iter = children_begin(shape);
	__constant t_shape	*nearest_negation_shape = NULL;

	*negation_t1 = INFINITY;
	*negation_t2 = INFINITY;
	while (has_next(&negation_children_iter))
	{
		__constant t_shape	*child = children_next(&negation_children_iter);
		if (child->relation_type != NEGATION)
			continue;
		// t1 is always less then t2
		t_scalar t1, t2;
		int nintersected_points = primitive_intersected(child, ray, &t1, &t2);
		// zero or only one intersected point are considered as infinitely small to negate
		if (nintersected_points < 2)
			continue;
		if (t1 < 1.0E-5 && t2 < 1.0E-5)
			continue;
		if (t1 > union_t1 && t1 > union_t2)
			continue;
		if (t2 < union_t1 && t2 < union_t2)
			continue;
		if ((t1 < 1.0E-5 && t2 > 1.0E-5 && t2 < *negation_t1)
		|| (t1 > 1.0E-5 && t1 < *negation_t1))
		{
			nearest_negation_shape = child;
			*negation_t1 = t1;
			*negation_t2 = t2;
		}
	}
	return (nearest_negation_shape);
}

__constant t_shape	*shape_intersected(__constant t_shape *shape, const t_ray *ray, t_scalar *t)
{
	if (shape->relation_type == NEGATION)
		return (NULL);
	if (shape->nchildren == 0)
		return (0 != primitive_intersected(shape, ray, t, NULL) ? shape : NULL);

	// find nearest union t
	t_scalar	union_t1, union_t2;

	__constant t_shape	*nearest_union_shape = union_intersected_shape(shape, ray, &union_t1, &union_t2);
	if (nearest_union_shape == NULL)
		return (NULL);

	// find nearest pair of two t which relates to closest negation shape
	t_scalar	negation_t1, negation_t2;

	__constant t_shape	*nearest_negation_shape = negation_intersected_shape(shape, ray, union_t1, union_t2, &negation_t1, &negation_t2);
	t_scalar	union_t = union_t1 < 1.0E-5 ? union_t2 : union_t1;
	if (nearest_negation_shape == NULL)
	{
		*t = union_t;
		return (nearest_union_shape);
	}
	if (negation_t1 < union_t1 && union_t2 < negation_t2)
		return (NULL);
	t_bool shape_is_negated = negation_t1 <= union_t && union_t <= negation_t2;
	*t = shape_is_negated ? negation_t2 : union_t;
	return (shape_is_negated ? nearest_negation_shape : nearest_union_shape);
}

int	primitive_intersected(__constant t_shape *shape, const t_ray *ray, t_scalar *t1, t_scalar *t2)
{
	__constant t_primitive *primitive = (__constant t_primitive*)shape_get_primitive(shape);
	t_scalar	*pt1 = t1;
	t_scalar	*pt2 = t2;
	t_scalar	dummy_t1;
	t_scalar	dummy_t2;

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
	else if (primitive->primitive_type == TORUS)
		return (torus_intersected(primitive, ray, pt1, pt2));
	return (0);
}

__constant t_shape	*cast_ray(const t_scene *scene,
const t_scene_buffers *buffers, const t_ray *ray, t_scalar *nearest_t)
{
	__constant t_shape	*nearest_shape = NULL;
	t_scalar			t;

	*nearest_t = INFINITY;
	t_iterator shape_iter = shape_begin(scene, buffers);
	while (has_next(&shape_iter))
	{
		__constant t_shape *shape = shape_next(&shape_iter);
		__constant t_shape *intersected_shape = NULL;
		if ((intersected_shape = shape_intersected(shape, ray, &t)) != NULL && t > 1.0E-5 && t < *nearest_t)
		{
			*nearest_t = t;
			nearest_shape = intersected_shape;
		}
	}
	return (nearest_shape);
}

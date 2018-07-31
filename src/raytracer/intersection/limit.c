/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "sceneiterator.h"

static t_vec4d	calc_global_point(const t_ray *ray, float t)
{
	t_vec3d	global_point;

	global_point = vec3d_scalar(&ray->direction, t);
	global_point = vec3d_add(&global_point, &ray->origin);
	return ((t_vec4d){global_point.x, global_point.y, global_point.z, 0.0f});
}

static t_vec4d	calc_transformed_point(const t_primitive *primitive, const t_vec4d *global_point)
{
	t_mat4d	orientation;
	t_vec4d	transformed_point;
	t_vec4d	position;
	t_vec4d	local_point;

	position = opencl_vec4_to_vec4(primitive->position);
	orientation = opencl_mat4x4_to_mat4x4(primitive->orientation);
	local_point = vec4d_sub(global_point, &position);
	transformed_point = mat4d_vec4d_mult(&orientation, &local_point);
	return (transformed_point);
}

static t_bool	is_cutted(const t_primitive *primitive, const t_limitation *limit,
const t_vec4d *global_point)
{
	t_axial_limitation	*axial_limit;
	t_vec4d				point;
	float				limit_value;

	axial_limit = (t_axial_limitation*)limitation_get_actual(limit);
	point = limit->is_relative ? calc_transformed_point(primitive, global_point) : *global_point;
	if (limit->limitation_type == XAXIS)
		limit_value = point.x;
	else if (limit->limitation_type == YAXIS)
		limit_value = point.y;
	else if (limit->limitation_type == ZAXIS)
		limit_value = point.z;
	if ((axial_limit->apply_if_less && limit_value < axial_limit->limit)
	|| (!axial_limit->apply_if_less && limit_value > axial_limit->limit))
		return (TRUE);
	return (FALSE);
}

t_bool			limit(const t_primitive *primitive, const t_ray *ray, float *target_t, const float t)
{
	t_iterator	limit_iter;
	t_vec4d		global_point;

	if (t < 0.0f)
		return (FALSE);
	limit_iter = limitation_begin(primitive);
	if (has_next(&limit_iter))
	{
		global_point = calc_global_point(ray, t);
		while (has_next(&limit_iter))
		{
			if (is_cutted(primitive, limitation_next(&limit_iter), &global_point))
				return (FALSE);
		}
	}
	*target_t = t;
	return (TRUE);
}

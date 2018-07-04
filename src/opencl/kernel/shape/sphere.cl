/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_bool sphere_limit(__constant t_primitive *primitive, __constant t_sphere *sphere, const t_ray *ray, t_scalar *t)
{
	t_iterator limit_iter = limitation_begin(primitive);
	if (has_next(&limit_iter))
	{
		const t_vec4 init_point = ray->origin + *t * ray->direction;
		const t_vec4 point = mat4x4_mult_vec4(primitive->orientation, init_point - primitive->position) + primitive->position;
		while (has_next(&limit_iter))
		{
			__constant t_limitation *limit = limitation_next(&limit_iter);
			if (IS_AXIAL(limit->limitation_type))
			{
				__constant t_axial_limitation *axial_limit = (__constant t_axial_limitation*)limitation_get_actual(limit);
				t_scalar axis;
				if (limit->limitation_type == XAXIS)
				{
					axis = limit->is_relative ? point.x - primitive->position.x : point.x;
					if ((axial_limit->apply_if_less && axis < axial_limit->limit) ||
					(!axial_limit->apply_if_less && axis > axial_limit->limit))
					{
						t_vec4 newpoint;
						newpoint.x = limit->is_relative ? axial_limit->limit + primitive->position.x : axial_limit->limit;
						newpoint.y = ((newpoint.x - point.x) * (point.y - ray->origin.y)) / (point.x - ray->origin.x) + point.y;
						newpoint.z = ((newpoint.x - point.x) * (point.z - ray->origin.z)) / (point.x - ray->origin.x) + point.z;
						newpoint.w = 0.0f;
						const t_vec4 to_new = newpoint - primitive->position;
						if (dot(to_new, to_new) <= sphere->radius2)
							*t = length(newpoint - ray->origin);
						else
							return (FALSE);
					}
				}
				if (limit->limitation_type == YAXIS)
				{
					axis = limit->is_relative ? point.y - primitive->position.y : point.y;
					if ((axial_limit->apply_if_less && axis < axial_limit->limit) ||
					(!axial_limit->apply_if_less && axis > axial_limit->limit))
					{
						t_vec4 lim = (t_vec4)(0.0f, axial_limit->limit, 0.0f, 0.0f);
						lim = mat4x4_mult_vec4(primitive->orientation, lim);
						// printf("%f %f %f %f\n", lim.x, lim.y, lim.z, lim.w);
						t_vec4 newpoint;
						newpoint.y = limit->is_relative ? lim.y + primitive->position.y : lim.y;
						newpoint.x = ((newpoint.y - point.y) * (point.x - ray->origin.x)) / (point.y - ray->origin.y) + point.x;
						newpoint.z = ((newpoint.y - point.y) * (point.z - ray->origin.z)) / (point.y - ray->origin.y) + point.z;
						newpoint.w = 0.0f;
						const t_vec4 to_new = newpoint - primitive->position;
						if (dot(to_new, to_new) <= sphere->radius2)
							*t = length(newpoint - ray->origin);
						else
							return (FALSE);
					}
				}
				if (limit->limitation_type == ZAXIS)
				{
					axis = limit->is_relative ? point.z - primitive->position.z : point.z;
					if ((axial_limit->apply_if_less && axis < axial_limit->limit) ||
					(!axial_limit->apply_if_less && axis > axial_limit->limit))
					{
						t_vec4 newpoint;
						newpoint.z = limit->is_relative ? axial_limit->limit + primitive->position.z : axial_limit->limit;
						newpoint.x = ((newpoint.z - point.z) * (point.x - ray->origin.x)) / (point.z - ray->origin.z) + point.x;
						newpoint.y = ((newpoint.z - point.z) * (point.y - ray->origin.y)) / (point.z - ray->origin.z) + point.y;
						newpoint.w = 0.0f;
						const t_vec4 to_new = newpoint - primitive->position;;
						if (dot(to_new, to_new) <= sphere->radius2)
							*t = length(newpoint - ray->origin);
						else
							return (FALSE);
					}
				}
			}
		}
	}
	return (TRUE);
}

t_bool	sphere_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t)
{
	__constant t_sphere *sphere = (__constant t_sphere*)primitive_get_actual(primitive);
	const t_vec4 to_orig = ray->origin - primitive->position;
	const t_scalar b = dot(ray->direction, to_orig);
	t_scalar d = b * b - (dot(to_orig, to_orig) - sphere->radius2);
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	*t = -b - d;
	if (*t < 0.0)
		*t = -b + d;
	if (*t < 0.0)
		return (FALSE);
	return (sphere_limit(primitive, sphere, ray, t));
}

t_vec4	obtain_sphere_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	t_iterator limit_iter = limitation_begin(primitive);
	if (has_next(&limit_iter))
	{
		// printf("%f %f %f %f\n", point->x - primitive->position.x,
		// point->y - primitive->position.y, point->z - primitive->position.z, point->w - primitive->position.w);
		while (has_next(&limit_iter))
		{
			__constant t_limitation *limit = limitation_next(&limit_iter);
			if (IS_AXIAL(limit->limitation_type))
			{
				__constant t_axial_limitation *axial_limit = (__constant t_axial_limitation*)limitation_get_actual(limit);
				if (limit->limitation_type == XAXIS)
				{
					t_scalar lim = limit->is_relative ? axial_limit->limit + primitive->position.x : axial_limit->limit;
					if (axial_limit->apply_if_less && fabs(point->x - lim) <= 1.0E-5)
						return ((t_vec4)(-1.0f, 0.0f, 0.0f, 0.0f));
					if (!axial_limit->apply_if_less && fabs(point->x - lim) <= 1.0E-5)
						return ((t_vec4)(1.0f, 0.0f, 0.0f, 0.0f));
				}
				if (limit->limitation_type == YAXIS)
				{
					t_scalar lim = limit->is_relative ? axial_limit->limit + primitive->position.y : axial_limit->limit;
					if (axial_limit->apply_if_less && fabs(point->y - lim) <= 1.0E-5)
						return (mat4x4_mult_vec4(primitive->orientation, (t_vec4)(0.0f, -1.0f, 0.0f, 0.0f)));
					if (!axial_limit->apply_if_less && fabs(point->y - lim) <= 1.0E-5)
						return ((t_vec4)(0.0f, 1.0f, 0.0f, 0.0f));
				}
				if (limit->limitation_type == ZAXIS)
				{
					t_scalar lim = limit->is_relative ? axial_limit->limit + primitive->position.z : axial_limit->limit;
					if (axial_limit->apply_if_less && fabs(point->z - lim) <= 1.0E-5)
						return ((t_vec4)(0.0f, 0.0f, -1.0f, 0.0f));
					if (!axial_limit->apply_if_less && fabs(point->z - lim) <= 1.0E-5)
						return ((t_vec4)(0.0f, 0.0f, 1.0f, 0.0f));
				}
			}
		}
	}
	return (normalize(*point - primitive->position));
}

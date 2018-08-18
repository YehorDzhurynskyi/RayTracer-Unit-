/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limitation.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_bool	limit(__constant t_primitive *primitive,
const t_ray *ray, t_scalar *target_t, const t_scalar t)
{
	t_iterator limit_iter = limitation_begin(primitive);
	if (has_next(&limit_iter))
	{
		const t_vec4 global_point = ray->origin + t * ray->direction;
		while (has_next(&limit_iter))
		{
			__constant t_limitation *limit = limitation_next(&limit_iter);
			__constant t_axial_limitation *axial_limit = (__constant t_axial_limitation*)limitation_get_actual(limit);
			const t_vec4 local_point = limit->is_relative ? mat4x4_mult_vec4(primitive->orientation, global_point - primitive->position) : global_point;
			t_scalar limit_value;
			if (limit->limitation_type == XAXIS)
				limit_value = local_point.x;
			else if (limit->limitation_type == YAXIS)
				limit_value = local_point.y;
			else if (limit->limitation_type == ZAXIS)
				limit_value = local_point.z;
			if ((axial_limit->apply_if_less && limit_value < axial_limit->limit)
			|| (!axial_limit->apply_if_less && limit_value > axial_limit->limit))
				return (FALSE);
		}
	}
	*target_t = t;
	return (TRUE);
}

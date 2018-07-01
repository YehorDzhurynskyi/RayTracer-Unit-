/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_bool			cylinder_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_cylinder *cylinder, float *t)
{
	const t_vec4 to_orig = ray->origin - shape->position;
	const t_vec4 va = cross(to_orig, cylinder->direction);
	const t_vec4 vb = cross(ray->direction, cylinder->direction);
	const float a = dot(vb, vb);
	const float b = dot(vb, va);
	float d = b * b - a * (dot(va, va) - cylinder->radius2);
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	*t = (-b - d) / a;
	if (*t < 0.0)
		*t = (-b + d) / a;
	return (TRUE);
}

inline t_vec4	cylinder_normal(const t_vec4 *point, __constant t_shape *shape,
__constant t_cylinder *cylinder)
{
	const t_vec4 to_orig = *point - shape->position;
	return (normalize(to_orig - (cylinder->direction * dot(to_orig, cylinder->direction))));
}

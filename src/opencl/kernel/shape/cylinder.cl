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

static t_vec4	cylinder_get_direction(__constant t_primitive *primitive)
{
	t_vec4 direction = (t_vec4)(primitive->orientation.s4, primitive->orientation.s5, primitive->orientation.s6, 0);
	return (-direction);
}

t_bool	cylinder_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t)
{
	__constant t_cylinder *cylinder = (__constant t_cylinder*)primitive_get_actual(primitive);
	const t_vec4 cylinder_direction = cylinder_get_direction(primitive);
	const t_vec4 to_orig = ray->origin - primitive->position;
	const t_vec4 va = cross(to_orig, cylinder_direction);
	const t_vec4 vb = cross(ray->direction, cylinder_direction);
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

t_vec4	obtain_cylinder_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	const t_vec4 to_orig = *point - primitive->position;
	const t_vec4 cylinder_direction = cylinder_get_direction(primitive);
	return (normalize(to_orig - (cylinder_direction * dot(to_orig, cylinder_direction))));
}

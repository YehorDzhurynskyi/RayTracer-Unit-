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
	return (TRUE);
}

t_vec4	obtain_sphere_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	return (normalize(*point - primitive->position));
}

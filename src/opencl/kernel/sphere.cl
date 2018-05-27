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

t_bool	sphere_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_sphere *sphere, float *t)
{
	const t_vec4 to_orig = ray->origin - shape->position;
	const float b = dot(ray->direction, to_orig);
	float d = b * b - (dot(to_orig, to_orig) - sphere->radius2);
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	*t = -b - d;
	if (*t < 0.0)
		*t = -b + d;
	return (TRUE);
}

inline t_vec4	sphere_normal(__constant t_shape *shape, const t_vec4 *point)
{
	return (normalize(*point - shape->position));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_vec4	plane_get_normal(__constant t_primitive *primitive)
{
	return ((t_vec4)(primitive->orientation.s4, primitive->orientation.s5, primitive->orientation.s6, 0));
}

t_bool	plane_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t)
{
	const t_vec4 plane_normal = plane_get_normal(primitive);
	float denom = -dot(ray->direction, plane_normal);
	float sign = 1.0f;
	if (denom < 0.0f)
	{
		denom = -denom;
		sign = -sign;
	}
	if (denom > 1e-6)
	{
		const t_vec4 to_plane = ray->origin - primitive->position;
		*t = sign * dot(to_plane, plane_normal);
		*t /= denom;
		return (*t > 0.0);
	}
	return (FALSE);
}

t_vec4	obtain_plane_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	return (plane_get_normal(primitive));
}

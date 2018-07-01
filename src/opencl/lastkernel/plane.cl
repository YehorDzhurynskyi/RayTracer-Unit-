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

static t_vec3	plane_get_normal(__constant t_primitive *primitive)
{
	return ((t_vec3)(primitive->orientation.s4, primitive->orientation.s5, primitive->orientation.s6));
}

t_bool				plane_intersect(const t_ray *ray, __constant t_primitive *primitive, float *t)
{
	const t_vec3 plane_normal = plane_get_normal(primitive);
	float denom = -dot(ray->direction, plane_normal);
	float sign = 1.0f;
	if (denom < 0.0f)
	{
		denom = -denom;
		sign = -sign;
	}
	if (denom > 1e-6)
	{
		const t_vec3 to_plane = ray->origin - primitive->position;
		*t = sign * dot(to_plane, plane_normal);
		*t /= denom;
		return (*t > 0.0);
	}
	return (FALSE);
}

inline t_vec3	plane_normal(__constant t_primitive *primitive)
{
	return (plane_get_normal(primitive));
}

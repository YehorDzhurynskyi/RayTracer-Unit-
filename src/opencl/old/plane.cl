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

t_bool	plane_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_plane *plane, float *t)
{
	float denom = -dot(ray->direction, plane->normal);
	float sign = 1.0f;
	if (denom < 0.0f)
	{
		denom = -denom;
		sign = -sign;
	}
	if (denom > 1e-6)
	{
		const t_vec4 to_plane = ray->origin - shape->position;
		*t = sign * dot(to_plane, plane->normal);
		*t /= denom;
		return (*t > 0.0);
	}
	return (FALSE);
}

inline t_vec4	plane_normal(__constant t_plane *plane)
{
	return (plane->normal);
}

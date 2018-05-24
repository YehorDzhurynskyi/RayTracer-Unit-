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

t_bool	sphere_intersect(const t_ray *ray, const t_shape *shape,
const t_sphere *sphere, float *t)
{
	float	b;
	float	d;

	float4 to_orig = ray->origin - shape->position;
	b = dot(ray->direction, to_orig);
	d = b * b - (dot(to_orig, to_orig) - sphere->radius2);
	if (d < 0.0)
		return (FALSE);
	*t = -b - sqrt(d);
	return (TRUE);
}

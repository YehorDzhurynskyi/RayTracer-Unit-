/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

inline static t_bool	is_cutted_cone(const t_ray *ray, __constant t_shape *shape,
__constant t_cone *cone, float t)
{
	const t_vec4 point = ray->origin - shape->position + ray->direction * t;
	return (dot(point, cone->direction) <= 0.0);
}

inline static float		find_scalar(const t_ray *ray, __constant t_shape *shape,
__constant t_cone *cone, const float t1, const float t2)
{
	const t_bool b1 = t1 < 0.0 || is_cutted_cone(ray, shape, cone, t1);
	const t_bool b2 = t2 < 0.0 || is_cutted_cone(ray, shape, cone, t2);
	if (b1 && b2)
		return (-1.0);
	if (b1)
		return (t2);
	else if (b2)
		return (t1);
	return (t1 < t2 ? t1 : t2);
}

t_bool					cone_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_cone *cone, float *t)
{
	const t_vec4 to_orig = ray->origin - shape->position;
	float a = dot(ray->direction, cone->direction);
	float c = dot(to_orig, cone->direction);
	const float b = a * c - dot(ray->direction, to_orig) * cone->cos2angle;
	a = a * a - cone->cos2angle;
	c = c * c - dot(to_orig, to_orig) * cone->cos2angle;
	float d = b * b - a * c;
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	*t = find_scalar(ray, shape, cone, (-b - d) / a, (-b + d) / a);
	return (*t > 0.0);
}

t_vec4					cone_normal(const t_vec4 *point, __constant t_shape *shape,
__constant t_cone *cone)
{
	const t_vec4 to_orig = *point - shape->position;
	return (normalize(to_orig - (cone->direction * dot(to_orig, cone->direction))));
}

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

static t_vec4	cone_get_direction(__constant t_primitive *primitive)
{
	t_vec4 direction = (t_vec4)(primitive->orientation.s4, primitive->orientation.s5, primitive->orientation.s6, 0.0f);
	return (-direction);
}

inline static t_bool	is_cutted_cone(__constant t_primitive *primitive, const t_ray *ray,
__constant t_cone *cone, float t)
{
	const t_vec4 cone_direction = cone_get_direction(primitive);
	const t_vec4 point = ray->origin - primitive->position + ray->direction * t;
	return (dot(point, cone_direction) <= 0.0);
}

inline static float		find_scalar(__constant t_primitive *primitive, const t_ray *ray,
__constant t_cone *cone, const float t1, const float t2)
{
	const t_bool b1 = t1 < 0.0 || is_cutted_cone(primitive, ray, cone, t1);
	const t_bool b2 = t2 < 0.0 || is_cutted_cone(primitive, ray, cone, t2);
	if (b1 && b2)
		return (-1.0);
	if (b1)
		return (t2);
	else if (b2)
		return (t1);
	return (t1 < t2 ? t1 : t2);
}

t_bool	cone_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t)
{
	__constant t_cone *cone = (__constant t_cone*)primitive_get_actual(primitive);
	const t_vec4 cone_direction = cone_get_direction(primitive);
	const t_vec4 to_orig = ray->origin - primitive->position;
	t_scalar a = dot(ray->direction, cone_direction);
	t_scalar c = dot(to_orig, cone_direction);
	const t_scalar b = a * c - dot(ray->direction, to_orig) * cone->cos2angle;
	a = a * a - cone->cos2angle;
	c = c * c - dot(to_orig, to_orig) * cone->cos2angle;
	t_scalar d = b * b - a * c;
	if (d < 0.0)
		return (FALSE);
	d = sqrt(d);
	*t = find_scalar(primitive, ray, cone, (-b - d) / a, (-b + d) / a);
	return (*t > 0.0);
}

inline t_vec4	obtain_cone_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	const t_vec4 cone_direction = cone_get_direction(primitive);
	const t_vec4 to_orig = *point - primitive->position;
	return (normalize(to_orig - (cone_direction * dot(to_orig, cone_direction))));
}

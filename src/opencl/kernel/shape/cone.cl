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
	t_vec4 direction = (t_vec4)(primitive->orientation.s4, primitive->orientation.s5, primitive->orientation.s6, 0);
	return (-direction);
}

inline static t_bool	is_cutted_cone(const t_ray *ray, __constant t_primitive *primitive,
__constant t_cone *cone, t_scalar t)
{
	const t_vec4 point = ray->origin - primitive->position + ray->direction * t;
	const t_vec4 cone_direction = cone_get_direction(primitive);
	return (dot(point, cone_direction) <= 0.0);
}

inline static t_bool	find_scalar(const t_ray *ray, __constant t_primitive *primitive,
__constant t_cone *cone, t_scalar *target_t, const t_scalar t1, const t_scalar t2)
{
	t_bool	t1_intersect;
	t_bool	t2_intersect;

	t1_intersect = TRUE;
	t2_intersect = TRUE;
	if (!limit(primitive, ray, target_t, t1) || is_cutted_cone(ray, primitive, cone, t1))
		t1_intersect = FALSE;
	if (!limit(primitive, ray, target_t, t2) || is_cutted_cone(ray, primitive, cone, t2))
		t2_intersect = FALSE;
	if (!t1_intersect && !t2_intersect)
		return (FALSE);
	if (t1_intersect && t2_intersect)
		*target_t = t1 < t2 ? t1 : t2;
	else if (t1_intersect)
		*target_t = t1_intersect ? t1 : t2;
	return (TRUE);
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
	return (find_scalar(ray, primitive, cone, t, (-b - d) / a, (-b + d) / a));
}

t_vec4	obtain_cone_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	const t_vec4 to_orig = *point - primitive->position;
	const t_vec4 cone_direction = cone_get_direction(primitive);
	return (normalize(to_orig - (cone_direction * dot(to_orig, cone_direction))));
}

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

int	sphere_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2)
{
	__constant t_sphere *sphere = (__constant t_sphere*)primitive_get_actual(primitive);
	const t_vec4 to_orig = ray->origin - primitive->position;
	const t_scalar b = dot(ray->direction, to_orig);
	t_scalar d = b * b - (dot(to_orig, to_orig) - sphere->radius2);
	if (d < 0.0f)
		return (0);
	d = sqrt(d);
	int nroots = 0;
	if (limit(primitive, ray, t1, -b - d))
		++nroots;
	if (limit(primitive, ray, t2, -b + d))
	{
		if (nroots == 0)
			*t1 = *t2;
		++nroots;
	}
	return (nroots);
}

t_vec4	obtain_sphere_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	const t_vec4 new_point = mat4x4_mult_vec4(primitive->orientation, *point - primitive->position) + primitive->position;
	return (normalize(new_point - primitive->position));
}

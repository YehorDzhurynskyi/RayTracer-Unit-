/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric_surface.cl                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	quadric_surface_intersected(__constant t_primitive *primitive, const t_ray *ray,
t_scalar *t1, t_scalar *t2)
{
	__constant t_quadric_surface	*quadric = (__constant t_quadric_surface*)primitive_get_actual(primitive);

	const t_vec4	origin = (t_vec4)(ray->origin.xyz, 1.0f);
	const t_vec4	direction = (t_vec4)(ray->direction.xyz, 1.0f);
	const t_vec4	transformed_origin = mat4x4_mult_vec4(quadric->coefs, origin);
	const t_vec4	transformed_direction = mat4x4_mult_vec4(quadric->coefs, direction);

	const t_scalar	a = dot(transformed_direction, direction);
	const t_scalar	b = 2.0f * dot(transformed_origin, direction);
	const t_scalar	c = dot(transformed_origin, origin);

	t_scalar	d = b * b - 4.0f * a * c;
	if (d < 0.0f)
		return (0);
	d = sqrt(d);
	*t1 = (-b - d) / (2.0f * a);
	*t1 < 0.0f ? (*t1 = (-b + d) / (2.0f * a)) : 0.0f;
	return (1);
}

t_vec4	obtain_quadric_surface_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	__constant t_quadric_surface	*quadric = (__constant t_quadric_surface*)primitive_get_actual(primitive);

	const t_vec4	translation = (t_vec4)(quadric->coefs.s47b, 0.0f);

	const t_vec4	transformed_point = (t_vec4)(mat4x4_mult_vec3(quadric->coefs, point->xyz).xyz, 0.0f);
	return (normalize(transformed_point + translation));
}

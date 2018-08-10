/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallelepiped.cl                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		parallelepiped_intersected(__constant t_primitive *primitive, const t_ray *ray,
t_scalar *t1, t_scalar *t2)
{
	__constant t_parallelepiped	*parallelepiped = (__constant t_parallelepiped*)primitive_get_actual(primitive);

	float2	xbounds = (float2)(primitive->position.x - parallelepiped->half_width, primitive->position.x + parallelepiped->half_width);
	float2	ybounds = (float2)(primitive->position.y - parallelepiped->half_height, primitive->position.y + parallelepiped->half_height);
	float2	zbounds = (float2)(primitive->position.z - parallelepiped->half_depth, primitive->position.z + parallelepiped->half_depth);

	const t_bool xsign = ray->direction.x >= 0.0f;
	const t_bool ysign = ray->direction.y >= 0.0f;
	const t_bool zsign = ray->direction.z >= 0.0f;

	const t_scalar txmin = (xbounds[xsign] - ray->origin.x) / ray->direction.x;
	const t_scalar txmax = (xbounds[1 - xsign] - ray->origin.x) / ray->direction.x;

	const t_scalar tymin = (ybounds[ysign] - ray->origin.y) / ray->direction.y;
	const t_scalar tymax = (ybounds[1 - ysign] - ray->origin.y) / ray->direction.y;

	const t_scalar tzmin = (zbounds[zsign] - ray->origin.z) / ray->direction.z;
	const t_scalar tzmax = (zbounds[1 - zsign] - ray->origin.z) / ray->direction.z;

	*t2 = max(max(txmin, tymin), tzmin);
	*t1 = min(min(txmax, tymax), tzmax);
	// printf("%f %f\n", *t1, *t2);
	if (*t1 > *t2)
		return (0);

	int nroots = 0;
	if (limit(primitive, ray, t1, *t1))
		++nroots;
	if (limit(primitive, ray, t2, *t2))
	{
		if (nroots == 0)
			*t1 = *t2;
		++nroots;
	}
	return (nroots);
}

t_vec4	obtain_parallelepiped_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvcoords.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	sphere_obtain_uv(__constant t_primitive *primitive,
const t_fragment *fragment, t_scalar *u, t_scalar *v)
{
	*u = 0.5f + atan2(fragment->normal.y, fragment->normal.x) / (M_PI * 2.0f);
	*v = 0.5f + asin(fragment->normal.z) / M_PI;
}

static void	plane_obtain_uv(__constant t_primitive *primitive,
const t_fragment *fragment, t_scalar *u, t_scalar *v)
{
	const t_vec4 new_point = mat4x4_mult_vec4(primitive->orientation, fragment->point);
	*u = new_point.x / 100 - (int)(new_point.x) / 100;
	*v = new_point.z / 100 - (int)(new_point.z) / 100;
}

static void	cylinder_obtain_uv(__constant t_primitive *primitive,
const t_fragment *fragment, t_scalar *u, t_scalar *v)
{
	const t_vec4 cyl_dir = (t_vec4)(primitive->orientation.s4, primitive->orientation.s5,
	primitive->orientation.s6, primitive->orientation.s7);
	const t_vec4 x_basis = (t_vec4)(primitive->orientation.s0, primitive->orientation.s1,
	primitive->orientation.s2, primitive->orientation.s3);
	const t_vec4 to_point = fragment->point - primitive->position;
	const t_scalar height_factor = dot(to_point, cyl_dir);
	const t_scalar arccos = acos(dot(fragment->normal, x_basis));
	*u = 0.5f + (isnan(arccos) ? 0.0f : arccos) / (2.0f * M_PI);
	*v = height_factor / 100 - (int)height_factor / 100;
}

void		obtain_uv(__constant t_primitive *primitive,
const t_fragment *fragment, t_scalar *u, t_scalar *v)
{
	if (primitive->primitive_type == SPHERE)
		sphere_obtain_uv(primitive, fragment, u, v);
	else if (primitive->primitive_type == PLANE)
		plane_obtain_uv(primitive, fragment, u, v);
	else if (primitive->primitive_type == CYLINDER)
		cylinder_obtain_uv(primitive, fragment, u, v);
	else if (primitive->primitive_type == CONE)
		cylinder_obtain_uv(primitive, fragment, u, v);
	else
	{
		*u = 0.0f;
		*v = 0.0f;
	}
}

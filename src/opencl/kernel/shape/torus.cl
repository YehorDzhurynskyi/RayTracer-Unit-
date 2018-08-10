/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	equation_4th_pow_for_tore(t_tore *tr, double *Q, double *abc, double *t, double *ray)
// {
// 	double  abcde[5];
// 	double  d;
// 	double  fore_R_2;
// 	double  rots[4];
// 	int     roots_num;

// 	d = dot_product(Q, Q) + tr->R * tr->R - tr->r * tr->r;
// 	fore_R_2 = 4 * tr->R * tr->R;
// 	abcde[4] = 1;
// 	abcde[3] = 4 * dot_product(Q, ray);
// 	abcde[2] = 2 * d + abcde[3] * abcde[3] / 4 - fore_R_2 * abc[0];
// 	abcde[1] = abcde[3] * d - fore_R_2 * abc[1];
// 	abcde[0] = d * d - fore_R_2 * abc[2];
// 	roots_num = SolveQuartic(abcde, rots);
// 	*t = 1e-6;
// 	for (int i = 0; i < roots_num; i++)
// 		if (rots[i] > 1e-6 && (*t == 1e-6 || rots[i] < *t))
// 			*t = rots[i];
// 	return (*t > 1e-6);
// }

static t_vec4	torus_get_direction(__constant t_primitive *primitive)
{
	t_vec4 direction = (t_vec4)(primitive->orientation.s4, primitive->orientation.s5, primitive->orientation.s6, 0);
	return (direction);
}

int	torus_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2)
{
	__constant t_torus *torus = (__constant t_torus*)primitive_get_actual(primitive);
	const t_vec4 ray_direction = normalize(ray->direction);
	const t_vec4 to_orig = ray->origin - primitive->position;
	const t_vec4 direction = torus_get_direction(primitive);
	const t_scalar u = dot(direction, to_orig);
	const t_scalar v = dot(direction, ray_direction);
	const t_scalar a = 1.0f - v * v;
	const t_scalar b = 2.0f * (dot(to_orig, ray_direction) - u * v);
	const t_scalar c = dot(to_orig, to_orig) - u * u;
	if (b * b - 4.0f * a * (c - (torus->far_radius + torus->near_radius)
	* (torus->far_radius + torus->near_radius)) < 0.0f)
		return (FALSE);
	const t_scalar d = dot(to_orig, to_orig) + torus->far_radius
	* torus->far_radius - torus->near_radius * torus->near_radius;
	const t_scalar e = 4.0f * torus->far_radius * torus->far_radius;
	const t_scalar f = 4.0f * dot(to_orig, ray_direction);
	double	roots[4];
	double	params[5];

	params[3] = d * d - e * c;
	params[2] = f * d - e * b;
	params[1] = 2.0f * d + f * f / 4.0f - e * a;
	params[0] = f;
	//const int nroots = solve_quartic(params, roots);
	const int nroots = fourth_degree_equation(&roots, params);
	if (nroots == 0)
		return (FALSE);

	// TODO: check roots properly
	// TODO: cut torus
	// TODO: return least two values
	*t1 = INFINITY;
	t_bool flag = TRUE;
	for (int i = 0; i < nroots; i++)
	{
		if (roots[i] > 1.0E-6 && roots[i] < *t1)
		{
			flag = FALSE;
			*t1 = roots[i];
		}
	}
	return (!flag && *t1 > 1.0E-5);
}

t_vec4	obtain_torus_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	// // const t_vec4 to_orig = mat4x4_mult_vec4(primitive->orientation, *point - primitive->position);
	__constant t_torus *torus = (__constant t_torus*)primitive_get_actual(primitive);
	const t_vec4 to_orig = *point - primitive->position;
	const t_vec4 direction = torus_get_direction(primitive);
	const t_vec4 new_point = normalize(to_orig - dot(to_orig, direction) * direction) * torus->far_radius;
	// // printf("normal\n");
	return (normalize(to_orig - new_point));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_reflect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec3f	vec3f_reflect(t_vec3f const *v, t_vec3f const *n)
{
	t_vec3f t;
	t_vec3f reflected;

	t = vec3f_scalar(n, 2.0f * vec3f_dot(v, n));
	reflected = vec3f_sub(v, &t);
	return (vec3f_normalize(&reflected));
}

inline t_vec3d	vec3d_reflect(t_vec3d const *v, t_vec3d const *n)
{
	t_vec3d t;
	t_vec3d reflected;

	t = vec3d_scalar(n, 2.0 * vec3d_dot(v, n));
	reflected = vec3d_sub(v, &t);
	return (vec3d_normalize(&reflected));
}

inline t_vec4f	vec4f_reflect(t_vec4f const *v, t_vec4f const *n)
{
	t_vec4f t;
	t_vec4f reflected;

	t = vec4f_scalar(n, 2.0f * vec4f_dot(v, n));
	reflected = vec4f_sub(v, &t);
	return (vec4f_normalize(&reflected));
}

inline t_vec4d	vec4d_reflect(t_vec4d const *v, t_vec4d const *n)
{
	t_vec4d t;
	t_vec4d reflected;

	t = vec4d_scalar(n, 2.0 * vec4d_dot(v, n));
	reflected = vec4d_sub(v, &t);
	return (vec4d_normalize(&reflected));
}

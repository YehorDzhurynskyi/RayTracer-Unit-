/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normilize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec3f	vec3f_normalize(t_vec3f const *v)
{
	float	l;

	l = vec3f_length(v);
	if (l == 0.0f)
		return (*v);
	return ((t_vec3f){v->x / l, v->y / l, v->z / l});
}

inline t_vec3d	vec3d_normalize(t_vec3d const *v)
{
	double	l;

	l = vec3d_length(v);
	if (l == 0.0)
		return (*v);
	return ((t_vec3d){v->x / l, v->y / l, v->z / l});
}

inline t_vec4f	vec4f_normalize(t_vec4f const *v)
{
	float	l;

	l = vec4f_length(v);
	if (l == 0.0f)
		return (*v);
	return ((t_vec4f){v->x / l, v->y / l, v->z / l, v->w / l});
}

inline t_vec4d	vec4d_normalize(t_vec4d const *v)
{
	double	l;

	l = vec4d_length(v);
	if (l == 0.0)
		return (*v);
	return ((t_vec4d){v->x / l, v->y / l, v->z / l, v->w / l});
}

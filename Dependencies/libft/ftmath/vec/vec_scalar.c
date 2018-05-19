/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scalar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec3f	vec3f_scalar(t_vec3f const *v, float s)
{
	return ((t_vec3f){v->x * s, v->y * s, v->z * s});
}

inline t_vec3d	vec3d_scalar(t_vec3d const *v, double s)
{
	return ((t_vec3d){v->x * s, v->y * s, v->z * s});
}

inline t_vec4f	vec4f_scalar(t_vec4f const *v, float s)
{
	return ((t_vec4f){v->x * s, v->y * s,
	v->z * s, v->w * s});
}

inline t_vec4d	vec4d_scalar(t_vec4d const *v, double s)
{
	return ((t_vec4d){v->x * s, v->y * s,
	v->z * s, v->w * s});
}

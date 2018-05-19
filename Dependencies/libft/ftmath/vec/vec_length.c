/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

inline float	vec3f_length(t_vec3f const *v)
{
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}

inline double	vec3d_length(t_vec3d const *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

inline float	vec4f_length(t_vec4f const *v)
{
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}

inline double	vec4d_length(t_vec4d const *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

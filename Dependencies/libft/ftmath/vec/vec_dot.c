/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline float	vec3f_dot(t_vec3f const *v1, t_vec3f const *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

inline double	vec3d_dot(t_vec3d const *v1, t_vec3d const *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

inline float	vec4f_dot(t_vec4f const *v1, t_vec4f const *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w);
}

inline double	vec4d_dot(t_vec4d const *v1, t_vec4d const *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w);
}

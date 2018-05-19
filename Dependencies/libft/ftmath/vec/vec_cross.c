/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cross.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:42:56 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/13 13:34:11 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec3f	vec3f_cross(t_vec3f const *v1, t_vec3f const *v2)
{
	return ((t_vec3f){v1->y * v2->z - v1->z * v2->y,
	v1->z * v2->x - v1->x * v2->z, v1->x * v2->y - v1->y * v2->x});
}

inline t_vec3d	vec3d_cross(t_vec3d const *v1, t_vec3d const *v2)
{
	return ((t_vec3d){v1->y * v2->z - v1->z * v2->y,
	v1->z * v2->x - v1->x * v2->z, v1->x * v2->y - v1->y * v2->x});
}

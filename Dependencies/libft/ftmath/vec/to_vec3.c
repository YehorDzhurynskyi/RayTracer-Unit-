/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_vec3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec3f	vec4f_to_vec3f(t_vec4f const *v)
{
	return ((t_vec3f){v->x / v->w, v->y / v->w, v->z / v->w});
}

inline t_vec3d	vec4d_to_vec3d(t_vec4d const *v)
{
	return ((t_vec3d){v->x / v->w, v->y / v->w, v->z / v->w});
}

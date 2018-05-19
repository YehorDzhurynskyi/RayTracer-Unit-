/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2rgba.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline unsigned int	vec3f2rgb(t_vec3f const *vec)
{
	unsigned int	res;

	res = (int)(vec->x * 255.0f) << 16;
	res |= (int)(vec->y * 255.0f) << 8;
	res |= (int)(vec->z * 255.0f) << 0;
	return (res);
}

inline unsigned int	vec3d2rgb(t_vec3d const *vec)
{
	unsigned int	res;

	res = (int)(vec->x * 255.0) << 16;
	res |= (int)(vec->y * 255.0) << 8;
	res |= (int)(vec->z * 255.0) << 0;
	return (res);
}

inline unsigned int	vec4f2rgba(t_vec4f const *vec)
{
	unsigned int	res;

	res = (int)(vec->x * 255.0f) << 16;
	res |= (int)(vec->y * 255.0f) << 8;
	res |= (int)(vec->z * 255.0f) << 0;
	res |= (int)(vec->w * 255.0f) << 24;
	return (res);
}

inline unsigned int	vec4d2rgba(t_vec4d const *vec)
{
	unsigned int	res;

	res = (int)(vec->x * 255.0) << 16;
	res |= (int)(vec->y * 255.0) << 8;
	res |= (int)(vec->z * 255.0) << 0;
	res |= (int)(vec->w * 255.0) << 24;
	return (res);
}

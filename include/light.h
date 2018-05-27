/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "opencl.h"

typedef enum
{
	POINTLIGHT = 1,
	SPOTLIGHT,
	DIRLIGHT
}	t_light_type;

typedef struct		__attribute__ ((packed)) s_light
{
	cl_uchar4		color;
	cl_float		intensity;
	cl_uint			buffer_offset;
	t_light_type	lighttype;
}	t_light;

typedef struct		__attribute__ ((packed)) s_pointlight
{
	t_clvec4		position;
	t_clvec4		attenuation;
}	t_pointlight;

typedef struct		__attribute__ ((packed)) s_dirlight
{
	t_clvec4		direction;
}	t_dirlight;

typedef struct		__attribute__ ((packed)) s_spotlight
{
	t_clvec4		position;
	t_clvec4		attenuation;
	t_clvec4		direction;
	cl_float		cosangle;
}	t_spotlight;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "opencl.h"

typedef enum
{
	PLANE = 1,
	SPHERE,
	CONE,
	CYLINDER
}	t_shape_type;

typedef struct		__attribute__ ((packed)) s_shape
{
	t_clvec4		position; // it's 16 bytes because of alignment
	cl_uchar4		color;
	cl_uint			buffer_offset;
	cl_float		shininess;
	cl_float		reflectivity;
	cl_float		opacity;
	cl_float		ior;
	t_shape_type	shapetype;
}	t_shape;

typedef struct		__attribute__ ((packed)) s_sphere
{
	cl_float		radius2;
}	t_sphere;

typedef struct		__attribute__ ((packed)) s_plane
{
	t_clvec4		normal;
}	t_plane;

typedef struct		__attribute__ ((packed)) s_cylinder
{
	t_clvec4		direction;
	cl_float		radius2;
}	t_cylinder;

typedef struct		__attribute__ ((packed)) s_cone
{
	t_clvec4		direction;
	cl_float		cos2angle;
}	t_cone;

#endif

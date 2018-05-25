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

# include "src/opencl/kernel/common.h"

typedef enum
{
	PLANE = 1,
	SPHERE,
	CONE,
	CYLINDER
}	t_shape_type;

typedef struct		__attribute__ ((packed)) s_shape
{
	t_vec4			position; // it's 16 bytes because of alignment
	uchar4			color;
	unsigned int	buffer_offset;
	t_shape_type	shapetype;
}	t_shape;

typedef struct		__attribute__ ((packed)) s_sphere
{
	float			radius2;
}	t_sphere;

typedef struct		__attribute__ ((packed)) s_plane
{
	float4			normal;
}	t_plane;


t_bool				sphere_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_sphere *sphere, float *t);
t_bool				plane_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_plane *plane, float *t);


# include "src/opencl/kernel/sphere.cl"
# include "src/opencl/kernel/plane.cl"

#endif

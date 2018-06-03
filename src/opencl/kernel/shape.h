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
	uint			buffer_offset;
	float			shininess;
	float			reflectivity;
	t_shape_type	shapetype;
}	t_shape;

typedef struct		__attribute__ ((packed)) s_sphere
{
	float			radius2;
}	t_sphere;

typedef struct		__attribute__ ((packed)) s_plane
{
	t_vec4			normal;
}	t_plane;

typedef struct		__attribute__ ((packed)) s_cylinder
{
	t_vec4			direction;
	float			radius2;
}	t_cylinder;

typedef struct		__attribute__ ((packed)) s_cone
{
	t_vec4			direction;
	float			cos2angle;
}	t_cone;

t_bool				sphere_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_sphere *sphere, float *t);
t_bool				plane_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_plane *plane, float *t);
t_bool				cylinder_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_cylinder *cylinder, float *t);
t_bool				cone_intersect(const t_ray *ray, __constant t_shape *shape,
__constant t_cone *cone, float *t);

t_vec4				sphere_normal(__constant t_shape *shape, const t_vec4 *point);
t_vec4				plane_normal(__constant t_plane *plane);
t_vec4				cylinder_normal(const t_vec4 *point, __constant t_shape *shape,
__constant t_cylinder *cylinder);
t_vec4				cone_normal(const t_vec4 *point, __constant t_shape *shape,
__constant t_cone *cone);

# include "src/opencl/kernel/sphere.cl"
# include "src/opencl/kernel/plane.cl"
# include "src/opencl/kernel/cylinder.cl"
# include "src/opencl/kernel/cone.cl"

#endif

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
	COMPOSITE = 1,
	POINT,
	PLANE,
	SPHERE,
	CONE,
	CYLINDER
}	t_primitive_type;

typedef enum
{
	UNION = 1,
	INTERSECTION,
	NEGATION
}	t_relation_type;

typedef int t_address;

typedef struct			__attribute__ ((packed))
{
	t_address			addr;
	t_address			material_addr;
	int					nchildren;
	t_relation_type		relation_type;
}	t_shape;

typedef struct			__attribute__ ((packed))
{
	t_vec3				position;
	t_mat4x4			orientation;
	int					nlimitations;
	t_primitive_type	primitive_type;
}	t_primitive;

// actual primitives

// plane is absent because it can be determined
// using orientation matrix in t_primitive structure
// so the normal vector is designeted as an y-basis vector

typedef struct			__attribute__ ((packed))
{
	t_scalar			radius2;
}	t_sphere;

typedef struct			__attribute__ ((packed))
{
	t_scalar			radius2;
}	t_cylinder;

typedef struct			__attribute__ ((packed))
{
	t_scalar			cos2angle;
}	t_cone;

t_bool				sphere_intersect(const t_ray *ray, __constant t_primitive *primitive,
__constant t_sphere *sphere, float *t);
t_bool				plane_intersect(const t_ray *ray, __constant t_primitive *primitive, float *t);
t_bool				cylinder_intersect(const t_ray *ray, __constant t_primitive *primitive,
__constant t_cylinder *cylinder, float *t);
t_bool				cone_intersect(const t_ray *ray, __constant t_primitive *primitive,
__constant t_cone *cone, float *t);

t_vec3				sphere_normal(__constant t_primitive *primitive, const t_vec3 *point);
t_vec3				plane_normal(__constant t_primitive *primitive);
t_vec3				cylinder_normal(const t_vec3 *point, __constant t_primitive *primitive);
t_vec3				cone_normal(const t_vec3 *point, __constant t_primitive *primitive);

# include "src/opencl/kernel/scene.h"

/*	MATERIAL */

# define DEFAULT_MATERIAL_ID	-1

typedef union
{
	t_scalar		value;
	int	id;
}	t_variant;

typedef struct		__attribute__ ((packed))
{
	int		addr;
	uchar4			color;
	t_variant		specularity;
	t_variant		glossiness;
	t_scalar		ior;
	int	normal_map;
	int	albedo_map;
}	t_material;

__constant t_material	*get_material(const t_scene *scene, __constant t_shape *shape);

__constant t_material	*get_material(const t_scene *scene, __constant t_shape *shape)
{
	__constant t_byte	*ptr = scene->materialbuffer + shape->material_addr;
	return ((__constant t_material*)ptr);
}

t_scalar	get_opacity(t_color color);

t_scalar	get_opacity(t_color color)
{
	return (1.0f - color.a / 255.0f);
}


/* MATERIAL */

# include "src/opencl/kernel/sphere.cl"
# include "src/opencl/kernel/plane.cl"
# include "src/opencl/kernel/cylinder.cl"
# include "src/opencl/kernel/cone.cl"

#endif

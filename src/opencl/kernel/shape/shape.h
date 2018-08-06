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

typedef enum
{
	COMPOSITE = 1,
	POINT,
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	TORUS
}	t_primitive_type;

typedef enum
{
	UNION = 1,
	INTERSECTION,
	NEGATION
}	t_relation_type;

typedef struct			__attribute__ ((packed))
{
	t_address			addr;
	t_address			material_addr;
	int					nchildren;
	t_relation_type		relation_type;
}	t_shape;

typedef struct			__attribute__ ((packed))
{
	t_mat4x4			orientation;
	t_vec4				position;
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

typedef struct			__attribute__ ((packed))
{
	t_scalar			far_radius;
	t_scalar			near_radius;
}	t_torus;

#endif

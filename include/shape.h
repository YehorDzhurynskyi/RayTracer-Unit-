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
	COMPOSITE = 1,
	POINT,
	PLANE,
	SPHERE,
	CONE,
	CYLINDER,
	TORUS
}	t_primitive_type;

# define ZERO_SIZE_PRIMITIVE(type) (type == POINT || type == COMPOSITE || type == PLANE)

typedef enum
{
	UNION = 1,
	INTERSECTION,
	NEGATION
}	t_relation_type;

typedef struct			__attribute__ ((packed))
{
	t_claddress			addr;
	t_claddress			material_addr;
	cl_int				nchildren;
	t_relation_type		relation_type;
}	t_shape;

typedef struct			__attribute__ ((packed))
{
	t_clmat4x4			orientation;
	t_clvec4			position;
	cl_int				nlimitations;
	t_primitive_type	primitive_type;
}	t_primitive;

typedef struct			__attribute__ ((packed))
{
	t_clscalar			radius2;
}	t_sphere;

typedef struct			__attribute__ ((packed))
{
	t_clscalar			radius2;
}	t_cylinder;

typedef struct			__attribute__ ((packed))
{
	t_clscalar			cos2angle;
}	t_cone;

typedef struct			__attribute__ ((packed))
{
	t_clscalar			far_radius;
	t_clscalar			near_radius;
}	t_torus;

#endif

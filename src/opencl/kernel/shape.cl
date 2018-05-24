/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/opencl/kernel/common.cl"

typedef enum e_shape_type	t_shape_type;
enum				e_shape_type
{
	PLANE = 0,
	SPHERE,
	CONE,
	CYLINDER
};

typedef struct s_shape t_shape;
struct				s_shape
{
	float4			position; // it's 16 bytes because of alignment
	uchar4			color;
	size_t			buffer_offset;
	t_shape_type	shapetype;
};

typedef struct s_sphere	t_sphere;
struct				s_sphere
{
	float			radius2;
};

t_bool				sphere_intersect(const t_ray *ray, const t_shape *shape,
const t_sphere *sphere, float *t);

#include "src/opencl/kernel/sphere.cl"
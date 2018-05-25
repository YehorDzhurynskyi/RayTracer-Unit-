/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/opencl/kernel/shape.h"

static t_bool		check_intersection(__constant t_byte **shape_ptr, const t_ray *ray,
float *t, __constant t_shape **shape)
{
	*shape = (__constant t_shape*)*shape_ptr;
	*shape_ptr += sizeof(t_shape);
	if ((*shape)->shapetype == SPHERE)
	{
		__constant t_sphere	*sphere = (__constant t_sphere*)*shape_ptr;
		*shape_ptr += sizeof(t_sphere);
		return (sphere_intersect(ray, *shape, sphere, t));
	}
	else if ((*shape)->shapetype == PLANE)
	{
		__constant t_plane	*plane = (__constant t_plane*)*shape_ptr;
		*shape_ptr += sizeof(t_plane);
		return (plane_intersect(ray, *shape, plane, t));
	}
	return (FALSE);
}

static __constant t_shape	*trace_shape(__constant t_byte *shapebuffer, int nshapes,
const t_ray *ray, float *nearest_t)
{
	__constant t_shape	*nearest_shape = NULL;
	__constant t_shape	*shape;
	float				t;

	*nearest_t = INFINITY;
	int i = -1;
	while (++i < nshapes)
	{
		if (FALSE == check_intersection(&shapebuffer, ray, &t, &shape))
			continue ;
		else if (t > 1.0E-5 && t < *nearest_t)
		{
			*nearest_t = t;
			nearest_shape = shape;
		}
	}
	return (nearest_shape);
}

static t_ray		obtain_primary_ray(t_camera camera, int x, int y, int width, int height)
{
	t_ray primary_ray = (t_ray){};
	float fov = tan(30.0f * M_PI / 180.0f); // TODO: set fov with config struct 
	float xd = (2.0f * ((x + 0.5f) / width) - 1.0) * fov * (width / (float)height);
	float yd = (1.0 - 2.0 * ((y + 0.5) / height)) * fov;
	primary_ray.origin = camera.position;
	primary_ray.direction = (float4)(xd, yd, -1.0f, 0.0f);
	primary_ray.direction = normalize(primary_ray.direction);
	primary_ray.direction = mat4x4_mult_vec4(camera.rotation_matrix,
	primary_ray.direction);
	return primary_ray;
}

__kernel void		trace(
	__global unsigned int *outputbuffer,
	__constant t_byte *shapebuffer,
	int nshapes,
	t_camera camera
)
{
	int	x = get_global_id(0);
	int	y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	t_ray primary_ray = obtain_primary_ray(camera, x, y, width, height);

	float t;
	__constant t_shape *shape = trace_shape(shapebuffer, nshapes, &primary_ray, &t);

	unsigned int color = 0;

	color |= shape->color.r << 16;
	color |= shape->color.g << 8;
	color |= shape->color.b << 0;
	color |= shape->color.a << 24;

	outputbuffer[x + y * width] = shape != 0 ? color : 0x0;
}

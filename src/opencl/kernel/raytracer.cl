/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.cl                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/opencl/kernel/raytracer.h"

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
	else if ((*shape)->shapetype == CYLINDER)
	{
		__constant t_cylinder	*cylinder = (__constant t_cylinder*)*shape_ptr;
		*shape_ptr += sizeof(t_cylinder);
		return (cylinder_intersect(ray, *shape, cylinder, t));
	}
	else if ((*shape)->shapetype == CONE)
	{
		__constant t_cone	*cone = (__constant t_cone*)*shape_ptr;
		*shape_ptr += sizeof(t_cone);
		return (cone_intersect(ray, *shape, cone, t));
	}
	return (FALSE);
}

__constant t_shape	*trace_shape(const t_scene *scene, const t_ray *ray, float *nearest_t)
{
	__constant t_byte	*shape_ptr;
	__constant t_shape	*nearest_shape = NULL;
	__constant t_shape	*shape;
	float				t;

	*nearest_t = INFINITY;
	int i = -1;
	shape_ptr = scene->shapebuffer;
	while (++i < scene->nshapes)
	{
		if (FALSE == check_intersection(&shape_ptr, ray, &t, &shape))
			continue ;
		else if (t > 1.0E-5 && t < *nearest_t)
		{
			*nearest_t = t;
			nearest_shape = shape;
		}
	}
	return (nearest_shape);
}

static uchar4		trace_ray(const t_ray *ray, const t_scene *scene, int trace_depth)
{
	uchar4				color;
	float				t;
	__constant t_shape	*shape;
	__constant t_shape	*next_shape;
	t_ray				next_ray = *ray;

	shape = (__constant t_shape*)trace_shape(scene, &next_ray, &t);
	if (shape == NULL)
		return (0);
	t_vec4 point = next_ray.direction * t + next_ray.origin;
	color = shade(&point, scene, shape);
	while (--trace_depth > 0)
	{
		if (shape->reflectivity < 1.0E-4)
			break;
		const t_vec4 normal = obtain_normal(&point, shape);
		next_ray.direction = reflected_vec(next_ray.direction, normal);
		const float bias = 0.005f;
		next_ray.origin = point + next_ray.direction * bias;
		next_shape = (__constant t_shape*)trace_shape(scene, &next_ray, &t);
		if (next_shape == NULL)
			break ;
		point = next_ray.direction * t + next_ray.origin;
		color = color_add(color, color_scalar(shade(&point, scene, next_shape), shape->reflectivity));
		shape = next_shape;
	}
	return (color);
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
	__global uchar4 *outputbuffer,
	__constant t_byte *shapebuffer,
	int nshapes,
	__constant t_byte *lightbuffer,
	int nlights,
	t_camera camera
)
{
	int	x = get_global_id(0);
	int	y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	t_scene scene;

	scene.shapebuffer = shapebuffer;
	scene.nshapes = nshapes;
	scene.lightbuffer = lightbuffer;
	scene.nlights = nlights;
	scene.camera = camera;

	t_ray primary_ray = obtain_primary_ray(camera, x, y, width, height);
	const uchar4 pixelcolor = trace_ray(&primary_ray, &scene, 5);
	outputbuffer[x + y * width] = pixelcolor;
}

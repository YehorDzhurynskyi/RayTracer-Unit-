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
	__constant t_primitive *prim = (__constant t_primitive*)*shape_ptr;
	*shape_ptr += sizeof(t_primitive);
	if (prim->primitive_type == SPHERE)
	{
		__constant t_sphere	*sphere = (__constant t_sphere*)*shape_ptr;
		*shape_ptr += sizeof(t_sphere);
		return (sphere_intersect(ray, prim, sphere, t));
	}
	else if (prim->primitive_type == PLANE)
	{
		return (plane_intersect(ray, prim, t));
	}
	else if (prim->primitive_type == CYLINDER)
	{
		__constant t_cylinder	*cylinder = (__constant t_cylinder*)*shape_ptr;
		*shape_ptr += sizeof(t_cylinder);
		return (cylinder_intersect(ray, prim, cylinder, t));
	}
	else if (prim->primitive_type == CONE)
	{
		__constant t_cone	*cone = (__constant t_cone*)*shape_ptr;
		*shape_ptr += sizeof(t_cone);
		return (cone_intersect(ray, prim, cone, t));
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
	while (++i < scene->meta.nshapes)
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

// static uchar4		trace_ray(const t_ray *ray, const t_scene *scene, int trace_depth)
// {
// 	float				t;
// 	__constant t_shape	*nearest_shape;
// 	t_ray				next_ray = *ray;
// 	uchar4				result_color = 0;
// 	float				reflectivity = 1.0f;

// 	do {
// 		nearest_shape = (__constant t_shape*)trace_shape(scene, &next_ray, &t);
// 		if (nearest_shape == NULL)
// 			break;
// 		const t_vec4 point = next_ray.direction * t + next_ray.origin;
// 		result_color = color_add(result_color, color_scalar(shade(&point, scene, nearest_shape), reflectivity * (1.0f - nearest_shape->reflectivity)));
// 		if (nearest_shape->reflectivity < 1.0e-6)
// 			break;
// 		reflectivity *= nearest_shape->reflectivity;
// 		const t_vec4 normal = obtain_normal(&point, nearest_shape);
// 		next_ray.direction = reflect(next_ray.direction, normal);
// 		const float bias = 0.005f;
// 		next_ray.origin = point + next_ray.direction * bias;
// 	} while (--trace_depth > 0);
// 	return (result_color);
// }

static t_vec3		refract(t_vec3 incident, t_vec3 normal, float ior)
{
	float cosi = dot(incident, normal); 
	float snell;
	if (cosi < 0)
	{
		cosi = -cosi;
		snell = 1.0f / ior; // here 1.0f is ior of vacuum
	}
	else
	{
		normal = -normal;
		snell = ior;
	}
	float k = 1 - snell * snell * (1 - cosi * cosi); 
	return (k < 0 ? 0 : snell * incident + (snell * cosi - sqrt(k)) * normal);
}

// TODO: implement call stack :) https://github.com/RenatoUtsch/clTracer/blob/master/source/clSampler/cl/recursion.cl

static uchar4		trace_ray(const t_scene *scene, const t_ray *ray)
{
	float				t;
	__constant t_shape	*nearest_shape;
	t_ray				next_ray = *ray;
	uchar4				result_color = 0;
	float				opacity = 1.0f;
	int					trace_depth = scene->config.trace_depth;

	do {
		nearest_shape = trace_shape(scene, &next_ray, &t);
		if (nearest_shape == NULL)
			break;
		__constant t_material *material = get_material(scene, nearest_shape);
		const t_vec3 point = next_ray.direction * t + next_ray.origin;
		const t_scalar nearest_shape_opacity = get_opacity(material->color);
		result_color = color_add(result_color, color_scalar(shade(&point, scene, nearest_shape), opacity * nearest_shape_opacity));
		if (nearest_shape_opacity == 1.0)
			break;
		opacity *= (1.0f - nearest_shape_opacity);
		const t_vec3 normal = obtain_normal(&point, nearest_shape);
		next_ray.direction = refract(next_ray.direction, normal, material->ior);
		const float bias = 0.005f;
		next_ray.origin = point + next_ray.direction * bias;
	} while (--trace_depth > 0);
	return (result_color);
}

static t_ray		obtain_camera_ray(const t_camera *camera, const t_scene_config *config,
int x, int y, int width, int height, float xbias, float ybias)
{
	t_ray camera_ray = (t_ray){};
	float fov = tan(config->fov / 2.0f * M_PI / 180.0f);
	float xd = (2.0f * ((x + xbias) / width) - 1.0) * fov * (width / (float)height);
	float yd = (1.0 - 2.0 * ((y + ybias) / height)) * fov;
	camera_ray.origin = camera->position;
	camera_ray.direction = (t_vec3)(xd, yd, -1.0f);
	camera_ray.direction = normalize(camera_ray.direction);
	camera_ray.direction = mat4x4_mult_vec3(camera->orientation,
	camera_ray.direction);
	return (camera_ray);
}

static t_color		trace_noaa(const t_scene *scene, int x, int y, int width, int height)
{
	const t_ray camera_ray = obtain_camera_ray(&scene->camera, &scene->config, x, y, width, height, 0.5f, 0.5f);
	return (trace_ray(scene, &camera_ray));
}

static t_color		trace_ssaax4(const t_scene *scene, int x, int y, int width, int height)
{
	const t_ray camera_ray1 = obtain_camera_ray(&scene->camera, &scene->config, x, y, width, height, 0.2f, 0.8f);
	const uchar4 pixelcolor1 = trace_ray(scene, &camera_ray1);
	const t_ray camera_ray2 = obtain_camera_ray(&scene->camera, &scene->config, x, y, width, height, 0.4f, 0.4f);
	const uchar4 pixelcolor2 = trace_ray(scene, &camera_ray2);
	const t_ray camera_ray3 = obtain_camera_ray(&scene->camera, &scene->config, x, y, width, height, 0.6f, 0.6f);
	const uchar4 pixelcolor3 = trace_ray(scene, &camera_ray3);
	const t_ray camera_ray4 = obtain_camera_ray(&scene->camera, &scene->config, x, y, width, height, 0.8f, 0.2f);
	const uchar4 pixelcolor4 = trace_ray(scene, &camera_ray4);

	return (color_add(
		color_add(
			color_scalar(pixelcolor1, 0.25f),
			color_scalar(pixelcolor2, 0.25f)),
		color_add(
			color_scalar(pixelcolor3, 0.25f),
			color_scalar(pixelcolor4, 0.25f))
		));
}

static t_color		trace_ssaax8(const t_scene *scene, int x, int y, int width, int height)
{
	// TODO: implement 8xSSAA
	return (trace_ssaax4(scene, x, y, width, height));
}

__kernel void		trace(
	__global t_color *outputbuffer,
	__constant t_byte *shapebuffer,
	__constant t_byte *lightsourcebuffer,
	__constant t_byte *materialbuffer,
	t_scenebuffer_meta meta,
	t_scene_config config,
	t_camera camera
)
{
	int	x = get_global_id(0);
	int	y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	t_scene scene;

	scene.shapebuffer = shapebuffer;
	scene.lightsourcebuffer = lightsourcebuffer;
	scene.materialbuffer = materialbuffer;
	scene.meta = meta;
	scene.config = config;
	scene.camera = camera;


	t_color	pixelcolor;
	if (config.aa == NOAA)
		pixelcolor = trace_noaa(&scene, x, y, width, height);
	else if (config.aa == SSAAx4)
		pixelcolor = trace_ssaax4(&scene, x, y, width, height);
	else if (config.aa == SSAAx8)
		pixelcolor = trace_ssaax8(&scene, x, y, width, height);
	outputbuffer[x + y * width] = pixelcolor;
}

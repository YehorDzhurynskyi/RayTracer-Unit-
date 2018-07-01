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

#include "types.h"
#include "math.h"
#include "math.cl"
#include "color.h"
#include "color.cl"
#include "scene/scene.h"
#include "shape/shape.h"

__constant t_shape	*cast_ray(const t_scene *scene, const t_ray *ray, t_scalar *nearest_t);

#include "material.h"
#include "material.cl"
#include "limitation/limitation.h"
#include "lightsource/lightsource.h"
#include "scene/sceneiterator.h"
#include "scene/sceneiterator.cl"
#include "shape/intersection.h"
#include "shape/cone.cl"
#include "shape/cylinder.cl"
#include "shape/sphere.cl"
#include "shape/plane.cl"
#include "shape/intersection.cl"

__constant t_shape	*cast_ray(const t_scene *scene, const t_ray *ray, t_scalar *nearest_t)
{
	__constant t_shape	*nearest_shape = NULL;
	t_scalar			t;

	*nearest_t = INFINITY;
	__constant t_byte	*ptr = scene->shapebuffer;
	int i = 0;
	while (i < scene->meta.nshapes)
	{
		// __constant t_shape	*shape = shape_next(&shape_iter);
		if (shape_intersected((__constant t_shape*)ptr, ray, &t) == FALSE || !(t > 1.0E-5 && t < *nearest_t))
		{
		}
		else
		{
			*nearest_t = t;
			nearest_shape = (__constant t_shape*)ptr;
		}
		ptr += sizeof(t_shape);
		__constant t_primitive *prim = (__constant t_primitive*)ptr;
		ptr += sizeof(t_primitive);
		if (prim->primitive_type == CONE)
			ptr += sizeof(t_cone);
		else if (prim->primitive_type == CYLINDER)
			ptr += sizeof(t_cylinder);
		else if (prim->primitive_type == SPHERE)
			ptr += sizeof(t_sphere);
		++i;
	}
	// t_iterator shape_iter = shape_begin(scene);
	// while (has_next(&shape_iter))
	// {
	// }
	return (nearest_shape);
}

static t_color		trace_ray(const t_scene *scene, const t_ray *ray)
{
	float				t;
	__constant t_shape	*nearest_shape;
	t_ray				next_ray = *ray;
	// uchar4				result_color = 0xff;
	// float				opacity = 1.0f;
	// int					trace_depth = scene->config.trace_depth;

	// // do {
		nearest_shape = cast_ray(scene, &next_ray, &t);
		if (nearest_shape == NULL)
			return (0);//break;
		__constant t_material *material = get_material(scene, nearest_shape);
		return (material->color);
	// 	// const t_vec3 point = next_ray.direction * t + next_ray.origin;
	// 	// const t_scalar nearest_shape_opacity = get_opacity(material->color);
	// 	// result_color = color_add(result_color, color_scalar(shade(&point, scene, nearest_shape), opacity * nearest_shape_opacity));
	// 	// if (nearest_shape_opacity == 1.0)
	// 	// 	break;
	// 	// opacity *= (1.0f - nearest_shape_opacity);
	// 	// const t_vec3 normal = obtain_normal(&point, nearest_shape);
	// 	// next_ray.direction = refract3(next_ray.direction, normal, material->ior);
	// 	// const float bias = 0.005f;
	// 	// next_ray.origin = point + next_ray.direction * bias;
	// // } while (--trace_depth > 0);
	return (0xff);
}

static t_ray		obtain_camera_ray(const t_camera *camera, const t_scene_config *config,
int x, int y, int width, int height, float xbias, float ybias)
{
	t_ray camera_ray = (t_ray){};
	float fov = tan(config->fov / 2.0f * M_PI / 180.0f);
	float xd = (2.0f * ((x + xbias) / width) - 1.0) * fov * (width / (float)height);
	float yd = (1.0 - 2.0 * ((y + ybias) / height)) * fov;
	camera_ray.origin = camera->position;
	camera_ray.direction = (t_vec4)(xd, yd, -1.0f, 0.0f);
	camera_ray.direction = normalize(camera_ray.direction);
	camera_ray.direction = mat4x4_mult_vec4(camera->orientation,
	camera_ray.direction);
	return (camera_ray);
}

static t_color		trace_noaa(const t_scene *scene, const t_camera *camera,
const t_scene_config *config, int x, int y, int width, int height)
{
	const t_ray camera_ray = obtain_camera_ray(camera, config, x, y, width, height, 0.5f, 0.5f);
	return (trace_ray(scene, &camera_ray));
}

static t_color		trace_ssaax4(const t_scene *scene, const t_camera *camera,
const t_scene_config *config, int x, int y, int width, int height)
{
	const t_ray camera_ray1 = obtain_camera_ray(camera, config, x, y, width, height, 0.2f, 0.8f);
	const uchar4 pixelcolor1 = trace_ray(scene, &camera_ray1);
	const t_ray camera_ray2 = obtain_camera_ray(camera, config, x, y, width, height, 0.4f, 0.4f);
	const uchar4 pixelcolor2 = trace_ray(scene, &camera_ray2);
	const t_ray camera_ray3 = obtain_camera_ray(camera, config, x, y, width, height, 0.6f, 0.6f);
	const uchar4 pixelcolor3 = trace_ray(scene, &camera_ray3);
	const t_ray camera_ray4 = obtain_camera_ray(camera, config, x, y, width, height, 0.8f, 0.2f);
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

static t_color		trace_ssaax8(const t_scene *scene, const t_camera *camera,
const t_scene_config *config, int x, int y, int width, int height)
{
	// TODO: implement 8xSSAA
	return (trace_ssaax4(scene, camera, config, x, y, width, height));
}

__kernel void	trace(
	__global t_color *outputbuffer,
	__constant t_byte *shapebuffer,
	__constant t_byte *lightsourcebuffer,
	__constant t_byte *materialbuffer,
	t_scenebuffer_meta scene_meta,
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
	scene.meta = scene_meta;
	scene.config = config;
	scene.camera = camera;

	t_color	pixelcolor;
	if (config.aa == NOAA)
		pixelcolor = trace_noaa(&scene, &camera, &config, x, y, width, height);
	else if (config.aa == SSAAx4)
		pixelcolor = trace_ssaax4(&scene, &camera, &config, x, y, width, height);
	else if (config.aa == SSAAx8)
		pixelcolor = trace_ssaax8(&scene, &camera, &config, x, y, width, height);
	outputbuffer[x + y * width] = pixelcolor;
}

// clang++ -mcpu=gfx802 -target amdgcn-amd-amdhsa-opencl -c -S -x cl -O3 src/opencl/kernel/raytracer.cl -I ~/libclc/generic/include -I src/opencl/kernel -include ~/libclc/generic/include/clc/clc.h
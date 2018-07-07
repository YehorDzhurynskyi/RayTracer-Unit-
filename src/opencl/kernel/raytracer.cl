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

#include "common/types.h"
#include "common/math.h"
#include "common/math.cl"
#include "common/color.h"
#include "common/color.cl"
#include "scene/scene.h"
#include "limitation/limitation.h"
#include "shape/shape.h"
#include "shading/shader.h"
#include "lightsource/lightsource.h"
#include "lightsource/illumination.h"
#include "scene/sceneiterator.h"
#include "scene/sceneiterator.cl"
#include "shape/intersection.h"
#include "shape/normal.h"
#include "shading/material.h"
#include "shading/material.cl"
#include "shape/sphere.cl"
#include "shape/plane.cl"
#include "shape/cylinder.cl"
#include "shape/cone.cl"
#include "lightsource/lightsource.cl"
#include "lightsource/pointlightsource.cl"
#include "lightsource/dirlightsource.cl"
#include "lightsource/spotlightsource.cl"
#include "shape/normal.cl"
#include "shape/intersection.cl"
#include "lightsource/illumination.cl"
#include "shading/dimness.cl"
#include "shading/shader.cl"

// // static uchar4		trace_ray(const t_ray *ray, const t_scene *scene, int trace_depth)
// // {
// // 	t_scalar				t;
// // 	__constant t_shape	*nearest_shape;
// // 	t_ray				next_ray = *ray;
// // 	uchar4				result_color = 0;
// // 	t_scalar				reflectivity = 1.0f;

// // 	do {
// // 		nearest_shape = (__constant t_shape*)cast_ray(scene, &next_ray, &t);
// // 		if (nearest_shape == NULL)
// // 			break;
// // 		const t_vec4 point = next_ray.direction * t + next_ray.origin;
// // 		result_color = color_add(result_color, color_scalar(shade(&point, scene, nearest_shape), reflectivity * (1.0f - nearest_shape->reflectivity)));
// // 		if (nearest_shape->reflectivity < 1.0e-6)
// // 			break;
// // 		reflectivity *= nearest_shape->reflectivity;
// // 		const t_vec4 normal = obtain_normal(&point, nearest_shape);
// // 		next_ray.direction = reflect(next_ray.direction, normal);
// // 		const t_scalar bias = 0.005f;
// // 		next_ray.origin = point + next_ray.direction * bias;
// // 	} while (--trace_depth > 0);
// // 	return (result_color);
// // }

// // TODO: implement call stack :) https://github.com/RenatoUtsch/clTracer/blob/master/source/clSampler/cl/recursion.cl

static t_rcolor		trace_ray(const t_scene *scene,
const t_scene_buffers *buffers, const t_ray *ray)
{
	t_scalar				t;
	__constant t_shape	*nearest_shape;
	t_ray				next_ray = *ray;
	t_rcolor			result_color = 0.0f;
	t_scalar				opacity = 1.0f;
	int					trace_depth = scene->config.trace_depth;
	const t_scalar		bias = 0.005f;

	do {
		nearest_shape = cast_ray(scene, buffers, &next_ray, &t);
		if (nearest_shape == NULL)
			break;
		__constant t_material *material = get_material(buffers, nearest_shape);
		const t_vec4 point = next_ray.direction * t + next_ray.origin;
		const t_scalar nearest_shape_opacity = get_opacity(material->diffuse_albedo.color);
		t_rcolor shape_color = shade(&point, &next_ray, scene, buffers, nearest_shape);
		if (scene->config.selected_shape_addr == nearest_shape->addr)
			shape_color = color_add(shape_color, (t_rcolor)(0.1f, 0.2f, 0.5f, 0));
		result_color = color_add(result_color, color_scalar(shape_color, opacity * nearest_shape_opacity));
		if (nearest_shape_opacity == 1.0)
			return (result_color);
		opacity *= (1.0f - nearest_shape_opacity);
		const t_vec4 normal = obtain_normal(&point, nearest_shape);
		next_ray.direction = refract4(next_ray.direction, normal, material->ior);
		next_ray.origin = point + next_ray.direction * bias;
		--trace_depth;
	} while (trace_depth > 0);
	return (result_color);
}

static t_ray		obtain_camera_ray(const t_scene *scene, int x, int y,
int width, int height, t_scalar xbias, t_scalar ybias)
{
	t_ray camera_ray = (t_ray){};
	t_scalar fov = tan(scene->config.fov / 2.0f * M_PI / 180.0f);
	t_scalar xd = (2.0f * ((x + xbias) / width) - 1.0) * fov * (width / (t_scalar)height);
	t_scalar yd = (1.0 - 2.0 * ((y + ybias) / height)) * fov;
	camera_ray.origin = scene->camera.position;
	camera_ray.direction = (t_vec4)(xd, yd, -1.0f, 0.0f);
	camera_ray.direction = normalize(camera_ray.direction);
	camera_ray.direction = mat4x4_mult_vec4(scene->camera.orientation,
	camera_ray.direction);
	return (camera_ray);
}

static t_rcolor		trace_noaa(const t_scene *scene, const t_scene_buffers *buffers,
int x, int y, int width, int height)
{
	const t_ray camera_ray = obtain_camera_ray(scene, x, y, width, height, 0.5f, 0.5f);
	return (trace_ray(scene, buffers, &camera_ray));
}

static t_rcolor		trace_ssaax4(const t_scene *scene, const t_scene_buffers *buffers,
int x, int y, int width, int height)
{
	const t_ray camera_ray1 = obtain_camera_ray(scene, x, y, width, height, 0.2f, 0.8f);
	const t_rcolor pixelcolor1 = trace_ray(scene, buffers, &camera_ray1);
	const t_ray camera_ray2 = obtain_camera_ray(scene, x, y, width, height, 0.4f, 0.4f);
	const t_rcolor pixelcolor2 = trace_ray(scene, buffers, &camera_ray2);
	const t_ray camera_ray3 = obtain_camera_ray(scene, x, y, width, height, 0.6f, 0.6f);
	const t_rcolor pixelcolor3 = trace_ray(scene, buffers, &camera_ray3);
	const t_ray camera_ray4 = obtain_camera_ray(scene, x, y, width, height, 0.8f, 0.2f);
	const t_rcolor pixelcolor4 = trace_ray(scene, buffers, &camera_ray4);

	return (color_add(
		color_add(
			color_scalar(pixelcolor1, 0.25f),
			color_scalar(pixelcolor2, 0.25f)),
		color_add(
			color_scalar(pixelcolor3, 0.25f),
			color_scalar(pixelcolor4, 0.25f))
		));
}

static t_rcolor		trace_ssaax8(const t_scene *scene, const t_scene_buffers *buffers,
int x, int y, int width, int height)
{
	// TODO: implement 8xSSAA
	return (trace_ssaax4(scene, buffers, x, y, width, height));
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

	scene.meta = meta;
	scene.config = config;
	scene.camera = camera;

	t_scene_buffers	buffers;

	buffers.shapebuffer = shapebuffer;
	buffers.lightsourcebuffer = lightsourcebuffer;
	buffers.materialbuffer = materialbuffer;

	t_rcolor	pixelcolor;
	if (config.aa == NOAA)
		pixelcolor = trace_noaa(&scene, &buffers, x, y, width, height);
	else if (config.aa == SSAAx4)
		pixelcolor = trace_ssaax4(&scene, &buffers, x, y, width, height);
	else if (config.aa == SSAAx8)
		pixelcolor = trace_ssaax8(&scene, &buffers, x, y, width, height);

	outputbuffer[x + y * width] = rcolor2color(pixelcolor);
}

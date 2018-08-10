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

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#include "common/types.h"
#include "common/math.h"
#include "common/queue.h"
#include "common/queue.cl"
#include "common/math.cl"
#include "common/color.h"
#include "common/color.cl"
#include "scene/scene.h"
#include "shading/texture.h"
#include "shape/shape.h"
#include "shading/material.h"
#include "shading/material.cl"
#include "shading/shader.h"
#include "lightsource/lightsource.h"
#include "lightsource/illumination.h"
#include "limitation/limitation.h"
#include "scene/sceneiterator.h"
#include "scene/sceneiterator.cl"
#include "limitation/limitation.cl"
#include "shape/intersection.h"
#include "shape/normal.h"
#include "shape/sphere.cl"
#include "shape/plane.cl"
#include "shape/cylinder.cl"
#include "shape/torus.cl"
#include "shape/quadric_surface.cl"
#include "shape/parallelepiped.cl"
#include "shape/cone.cl"
#include "lightsource/lightsource.cl"
#include "lightsource/pointlightsource.cl"
#include "lightsource/dirlightsource.cl"
#include "lightsource/spotlightsource.cl"
#include "shape/normal.cl"
#include "shape/intersection.cl"
#include "lightsource/illumination.cl"
#include "shading/fragment.cl"
#include "shading/dimness.cl"
#include "shading/texture.cl"
#include "shading/uvcoords.cl"
#include "shading/shader.cl"

const sampler_t skyboxsampler = CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_CLAMP | CLK_FILTER_LINEAR;

static t_rcolor		map_skybox(__read_only image2d_array_t skybox, const t_ray *ray)
{
	float absX = fabs(ray->direction.x);
	float absY = fabs(ray->direction.y);
	float absZ = fabs(ray->direction.z);

	int isXPositive = ray->direction.x > 0 ? 1 : 0;
	int isYPositive = ray->direction.y > 0 ? 1 : 0;
	int isZPositive = ray->direction.z > 0 ? 1 : 0;
	
	int index = 0;

	float maxAxis, uc, vc;
	
	// POSITIVE X
	if (isXPositive && absX >= absY && absX >= absZ) {
	// u (0 to 1) goes from +z to -z
	// v (0 to 1) goes from -y to +y
	maxAxis = absX;
	uc = -ray->direction.y;
	vc = -ray->direction.z;
	index = 0;
		//return 0x88;
	}
	// NEGATIVE X
	else if (!isXPositive && absX >= absY && absX >= absZ) {
	// u (0 to 1) goes from -z to +z
	// v (0 to 1) goes from -y to +y
	maxAxis = absX;
	uc = ray->direction.y;
	vc = -ray->direction.z;
	index = 1;
		//return 0xFF;
	}
	// POSITIVE Y
	else if (isYPositive && absY >= absX && absY >= absZ) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from +z to -z
	maxAxis = absY;
	uc = ray->direction.x;
	vc = -ray->direction.z;
	index = 2;
		//return 0x8800;
	}
	// NEGATIVE Y
	else if (!isYPositive && absY >= absX && absY >= absZ) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from -z to +z
	maxAxis = absY;
	uc = -ray->direction.x;
	vc = -ray->direction.z;
	index = 3;
		//return 0xFF00;
	}
	// POSITIVE Z
	else if (isZPositive && absZ >= absX && absZ >= absY) {
	// u (0 to 1) goes from -x to +x
	// v (0 to 1) goes from -y to +y
	maxAxis = absZ;
	uc = -ray->direction.y;
	vc = ray->direction.x;
	index = 4;
		//return 0x880000;
	}
	// NEGATIVE Z
	else if (!isZPositive && absZ >= absX && absZ >= absY) {
	// u (0 to 1) goes from +x to -x
	// v (0 to 1) goes from -y to +y
	maxAxis = absZ;
	uc = -ray->direction.y;
	vc = -ray->direction.x;
	index = 5;
		//return 0xFF0000;
	}
	uc = 0.5f * (uc / maxAxis + 1.0f);
	vc = 0.5f * (vc / maxAxis + 1.0f);
	t_vec4 col = read_imagef(skybox, skyboxsampler, (float4)(uc, vc, (float)index, 0.0f));
	col.x = 0.0f;
	return (col.wzyx);
}

static t_rcolor		trace_ray(const t_scene *scene, const t_scene_buffers *buffers,
__read_only image2d_array_t textures, __read_only image2d_array_t skybox, const t_ray *ray)
{
	t_queue			trace_queue = queue_init();
	t_scalar		t;
	t_rcolor		result_color = 0.0f;
	// int			trace_depth = 3;// TODO: uncomment: scene->config.trace_depth;
	const t_scalar	bias = 0.005f;

	t_queue_elem	current_elem;
	current_elem.ray = *ray;
	current_elem.intensity = 1.0f;
	do {
		t_rcolor current_color = 0.0f;
		__constant t_shape *nearest_shape = cast_ray(scene, buffers, &current_elem.ray, &t);
		t_scalar light_t = t;
		__constant t_lightsource *nearest_lightsource = cast_lightsource_ray(scene, buffers, &current_elem.ray, &light_t);
		if (nearest_lightsource != NULL && light_t < t)
		{
			current_color = color2rcolor(nearest_lightsource->color);
		}
		else if (nearest_shape == NULL)
		{
			current_color = map_skybox(skybox, &current_elem.ray);
		}
		else
		{
			const t_fragment fragment = compose_fragment(buffers, textures, nearest_shape, &current_elem.ray, t);
			current_color = shade(scene, buffers, textures, &fragment);
			const t_scalar nearest_shape_opacity = 1.0f - fragment.diffuse_albedo.a;
			// (t + r <= 1.0) -> (1.0 - o + r <= 1.0) -> (r - o <= 0.0) -> (r <= o)
			current_color *= fragment.glossiness <= nearest_shape_opacity ? nearest_shape_opacity - fragment.glossiness : 0.0f;
			// fresnel
			if (current_elem.intensity * fragment.glossiness > 0.095f)
			{
				t_queue_elem	new_elem;
				new_elem.ray.direction = reflect4(current_elem.ray.direction, fragment.normal);
				new_elem.ray.origin = fragment.point + new_elem.ray.direction * bias;
				new_elem.intensity = current_elem.intensity * fragment.glossiness;
				queue_push(&trace_queue, &new_elem);
			}
			if (current_elem.intensity * (1.0f - nearest_shape_opacity) > 0.095f)
			{
				t_queue_elem	new_elem;
				new_elem.ray.direction = refract4(current_elem.ray.direction, fragment.normal, fragment.ior);
				new_elem.ray.origin = fragment.point + new_elem.ray.direction * bias;
				new_elem.intensity = current_elem.intensity * (1.0f - nearest_shape_opacity);
				queue_push(&trace_queue, &new_elem);
			}
			if (scene->config.selected_shape_addr == nearest_shape->addr)
				current_color += (t_rcolor)(0.1f, 0.2f, 0.5f, 0.0f);
		}
		result_color += current_color * current_elem.intensity;
	} while (queue_pop(&trace_queue, &current_elem) == TRUE);
	return (result_color);
}

static t_ray		obtain_camera_ray(const t_scene *scene, t_scalar xbias, t_scalar ybias)
{
	t_ray camera_ray = (t_ray){};
	t_scalar fov = tan(scene->config.fov / 2.0f * M_PI / 180.0f);
	t_scalar xd = (2.0f * ((scene->x + xbias) / scene->width) - 1.0) * fov * (scene->width / (t_scalar)scene->height);
	t_scalar yd = (1.0 - 2.0 * ((scene->y + ybias) / scene->height)) * fov;
	camera_ray.origin = scene->camera.position;
	camera_ray.direction = (t_vec4)(xd, yd, -1.0f, 0.0f);
	camera_ray.direction = normalize(camera_ray.direction);
	camera_ray.direction = mat4x4_mult_vec4(scene->camera.orientation,
	camera_ray.direction);
	return (camera_ray);
}

static t_rcolor		trace_noaa(const t_scene *scene, const t_scene_buffers *buffers,
__read_only image2d_array_t skybox, __read_only image2d_array_t textures)
{
	const t_ray camera_ray = obtain_camera_ray(scene, 0.5f, 0.5f);
	return (trace_ray(scene, buffers, textures, skybox, &camera_ray));
}

static t_rcolor		trace_ssaax4(const t_scene *scene, const t_scene_buffers *buffers,
__read_only image2d_array_t skybox, __read_only image2d_array_t textures)
{
	const t_ray camera_ray1 = obtain_camera_ray(scene, 0.2f, 0.8f);
	const t_rcolor pixelcolor1 = trace_ray(scene, buffers, textures, skybox, &camera_ray1);
	const t_ray camera_ray2 = obtain_camera_ray(scene, 0.4f, 0.4f);
	const t_rcolor pixelcolor2 = trace_ray(scene, buffers, textures, skybox, &camera_ray2);
	const t_ray camera_ray3 = obtain_camera_ray(scene, 0.6f, 0.6f);
	const t_rcolor pixelcolor3 = trace_ray(scene, buffers, textures, skybox, &camera_ray3);
	const t_ray camera_ray4 = obtain_camera_ray(scene, 0.8f, 0.2f);
	const t_rcolor pixelcolor4 = trace_ray(scene, buffers, textures, skybox, &camera_ray4);

	return ((pixelcolor1 + pixelcolor2 + pixelcolor3 + pixelcolor4) / 4.0f);
}

static t_rcolor		trace_ssaax8(const t_scene *scene, const t_scene_buffers *buffers,
__read_only image2d_array_t skybox, __read_only image2d_array_t textures)
{
	// TODO: implement 8xSSAA
	return (trace_ssaax4(scene, buffers, skybox, textures));
}

__kernel void		trace(
	__global t_color *outputbuffer,
	__constant t_byte *shapebuffer,
	__constant t_byte *lightsourcebuffer,
	__constant t_byte *materialbuffer,
	__constant t_byte *texturebuffer,
	__read_only image2d_array_t skybox,
	__read_only image2d_array_t textures,
	t_scenebuffer_meta meta,
	t_scene_config config,
	t_camera camera
)
{
	t_scene scene;

	scene.meta = meta;
	scene.config = config;
	scene.camera = camera;
	scene.x = get_global_id(0);
	scene.y = get_global_id(1);
	scene.width = get_global_size(0);
	scene.height = get_global_size(1);

	t_scene_buffers	buffers;

	buffers.shapebuffer = shapebuffer;
	buffers.lightsourcebuffer = lightsourcebuffer;
	buffers.materialbuffer = materialbuffer;
	buffers.texturebuffer = texturebuffer;

	t_rcolor	pixelcolor;
	if (config.aa == NOAA)
		pixelcolor = trace_noaa(&scene, &buffers, skybox, textures);
	else if (config.aa == SSAAx4)
		pixelcolor = trace_ssaax4(&scene, &buffers, skybox, textures);
	else if (config.aa == SSAAx8)
		pixelcolor = trace_ssaax8(&scene, &buffers, skybox, textures);

	outputbuffer[scene.x + scene.y * scene.width] = rcolor2color(pixelcolor);
}

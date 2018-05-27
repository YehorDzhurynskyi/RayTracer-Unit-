/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/opencl/kernel/shader.h"

static t_bool	is_in_shadow(const t_vec4 *point, const t_scene *scene, __constant t_byte *light_ptr)
{
	__constant t_light *light = (__constant t_light*)light_ptr;
	t_vec4	to_light;
	if (light->lighttype == POINTLIGHT)
	{
		__constant t_pointlight *pointlight = (__constant t_pointlight*)(light_ptr + sizeof(t_light));
		to_light = pointlight_to(pointlight, point);
	}
	else if (light->lighttype == DIRLIGHT)
	{
		__constant t_dirlight *dirlight = (__constant t_dirlight*)(light_ptr + sizeof(t_light));
		to_light = dirlight_to(dirlight);
	}
	else if (light->lighttype == SPOTLIGHT)
	{
		__constant t_spotlight *spotlight = (__constant t_spotlight*)(light_ptr + sizeof(t_light));
		to_light = spotlight_to(spotlight, point);
	}
	const t_vec4 shadow_ray_direction = normalize(to_light);
	const float bias = 0.005f;
	t_ray	shadow_ray = (t_ray){*point + shadow_ray_direction * bias, shadow_ray_direction};
	float t;
	if (NULL != trace_shape(scene, &shadow_ray, &t))
	{
		if (light->lighttype == POINTLIGHT)
			return (pointlight_in_shadow(&to_light, t));
		else if (light->lighttype == DIRLIGHT)
			return (dirlight_in_shadow());
		else if (light->lighttype == SPOTLIGHT)
		{
			__constant t_spotlight *spotlight = (__constant t_spotlight*)(light_ptr + sizeof(t_light));
			return (spotlight_in_shadow(spotlight, &to_light, t));
		}
	}
	return (FALSE);
}

static uchar4	illuminate(__constant t_byte *lightbuffer, const t_fragment *fragment)
{
	__constant t_light *light = (__constant t_light*)lightbuffer;
	if (light->lighttype == POINTLIGHT)
	{
		__constant t_pointlight *pointlight = (__constant t_pointlight*)(lightbuffer + sizeof(t_light));
		return (pointlight_illuminate(light, pointlight, fragment));
	}
	else if (light->lighttype == DIRLIGHT)
	{
		__constant t_dirlight *dirlight = (__constant t_dirlight*)(lightbuffer + sizeof(t_light));
		return (dirlight_illuminate(light, dirlight, fragment));
	}
	else if (light->lighttype == SPOTLIGHT)
	{
		__constant t_spotlight *spotlight = (__constant t_spotlight*)(lightbuffer + sizeof(t_light));
		return (spotlight_illuminate(light, spotlight, fragment));
	}
	return (0);
}

static t_vec4	obtain_normal(const t_vec4 *point, __constant t_shape *shape)
{
	const __constant t_byte *shape_ptr = (__constant t_byte*)shape;
	if (shape->shapetype == SPHERE)
		return (sphere_normal(shape, point));
	else if (shape->shapetype == PLANE)
	{
		__constant t_plane *plane = (__constant t_plane*)(shape_ptr + sizeof(t_shape));
		return (plane_normal(plane));
	}
	else if (shape->shapetype == CYLINDER)
	{
		__constant t_cylinder *cylinder = (__constant t_cylinder*)(shape_ptr + sizeof(t_shape));
		return (cylinder_normal(point, shape, cylinder));
	}
	else if (shape->shapetype == CONE)
	{
		__constant t_cone *cone = (__constant t_cone*)(shape_ptr + sizeof(t_shape));
		return (cone_normal(point, shape, cone));
	}
	return (0);
}

inline static t_fragment	compose_fragment(const t_scene *scene, const t_vec4 *point, __constant t_shape *shape)
{
	t_fragment	fragment;

	fragment.normal = obtain_normal(point, shape);
	fragment.color = shape->color;
	fragment.to_eye = scene->camera.position - shape->position;
	fragment.point = *point;
	return (fragment);
}

uchar4	shade(const t_vec4 *point, const t_scene *scene, __constant t_shape *shape)
{
	const float ambient = 0.15f;
	uchar4	color = color_scalar(shape->color, ambient); // TODO: replace hardcoded ambient factor
	__constant t_byte *light_ptr = scene->lightbuffer;
	int i = -1;
	const t_fragment fragment = compose_fragment(scene, point, shape);
	while (++i < scene->nlights)
	{
		__constant t_light *light = (__constant t_light*)light_ptr;
		if (!is_in_shadow(point, scene, light_ptr)) // TODO: add soft shadows
			color = color_add(color, illuminate(light_ptr, &fragment));
		if (light->lighttype == POINTLIGHT)
			light_ptr += sizeof(t_light) + sizeof(t_pointlight);
		else if (light->lighttype == DIRLIGHT)
			light_ptr += sizeof(t_light) + sizeof(t_dirlight);
		else if (light->lighttype == SPOTLIGHT)
			light_ptr += sizeof(t_light) + sizeof(t_spotlight);
	}
	return (color);
}

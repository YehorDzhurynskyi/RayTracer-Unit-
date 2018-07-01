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

//static float	dimness(const t_vec4 *point, const t_scene *scene, __constant t_byte *light_ptr)
//{
//	__constant t_light *light = (__constant t_light*)light_ptr;
//	t_vec4	to_light;
//	if (light->lighttype == POINTLIGHT)
//	{
//		__constant t_pointlight *pointlight = (__constant t_pointlight*)(light_ptr + sizeof(t_light));
//		to_light = pointlight_to(pointlight, point);
//	}
//	else if (light->lighttype == DIRLIGHT)
//	{
//		__constant t_dirlight *dirlight = (__constant t_dirlight*)(light_ptr + sizeof(t_light));
//		to_light = dirlight_to(dirlight);
//	}
//	else if (light->lighttype == SPOTLIGHT)
//	{
//		__constant t_spotlight *spotlight = (__constant t_spotlight*)(light_ptr + sizeof(t_light));
//		to_light = spotlight_to(spotlight, point);
//	}
//	const t_vec4 shadow_ray_direction = normalize(to_light);
//	const float bias = 0.005f;
//	t_ray	shadow_ray = (t_ray){*point + shadow_ray_direction * bias, shadow_ray_direction};
//	float t;
//	__constant t_shape *nearest_shape = trace_shape(scene, &shadow_ray, &t);
//	if (nearest_shape != NULL)
//	{
//		if (light->lighttype == POINTLIGHT)
//			return (pointlight_in_shadow(&to_light, t) * nearest_shape->opacity);
//		else if (light->lighttype == DIRLIGHT)
//			return (dirlight_in_shadow() * nearest_shape->opacity);
//		else if (light->lighttype == SPOTLIGHT)
//		{
//			__constant t_spotlight *spotlight = (__constant t_spotlight*)(light_ptr + sizeof(t_light));
//			return (spotlight_in_shadow(spotlight, &to_light, t) * nearest_shape->opacity);
//		}
//	}
//	return (0.0);
//}

static uchar4	illuminate(__constant t_byte *lightbuffer, const t_fragment *fragment)
{
	__constant t_lightsource *lightsource = (__constant t_lightsource*)lightbuffer;
	if (lightsource->lightsource_type == POINTLIGHT)
	{
		__constant t_pointlightsource *pointlightsource = (__constant t_pointlightsource*)(lightbuffer + sizeof(t_lightsource));
		return (pointlightsource_illuminate(lightsource, pointlightsource, fragment));
	}
	else if (lightsource->lightsource_type == DIRLIGHT)
	{
		__constant t_dirlightsource *dirlightsource = (__constant t_dirlightsource*)(lightbuffer + sizeof(t_lightsource));
		return (dirlightsource_illuminate(lightsource, dirlightsource, fragment));
	}
	else if (lightsource->lightsource_type == SPOTLIGHT)
	{
		__constant t_spotlightsource *spotlightsource = (__constant t_spotlightsource*)(lightbuffer + sizeof(t_lightsource));
		return (spotlightsource_illuminate(lightsource, spotlightsource, fragment));
	}
	return (0);
}

t_vec3	obtain_normal(const t_vec3 *point, __constant t_shape *shape)
{
	const __constant t_byte *shape_ptr = (__constant t_byte*)shape;
	shape_ptr += sizeof(t_shape);
	__constant t_primitive *primitive = (__constant t_primitive*)shape_ptr;
	if (primitive->primitive_type == SPHERE)
		return (sphere_normal(primitive, point));
	else if (primitive->primitive_type == PLANE)
	{
		return (plane_normal(primitive));
	}
	else if (primitive->primitive_type == CYLINDER)
	{
		return (cylinder_normal(point, primitive));
	}
	else if (primitive->primitive_type == CONE)
	{
		return (cone_normal(point, primitive));
	}
	return (0);
}

static t_fragment	compose_fragment(const t_scene *scene,
const t_vec3 *point, __constant t_shape *shape)
{
	t_fragment	fragment;
	__constant t_material *material = get_material(scene, shape);
	__constant t_byte *ptr = (__constant t_byte*)shape;
	ptr += sizeof(t_shape);
	__constant t_primitive *primitive = (__constant t_primitive*)ptr;

	fragment.point = *point;
	fragment.normal = obtain_normal(point, shape);
	fragment.to_eye = (t_vec3)(0.0, 0.0, 1.0);
	// fragment.to_eye = normalize(scene->camera.position - primitive->position);
	fragment.color = material->color;
	fragment.shininess = (1.0 - material->specularity.value) * 255.0;
	//fragment.specularity = (1.0 - material->specularity.value) * 255.0;
	//fragment.glossiness = material->glossiness.value;
	return (fragment);
}

uchar4	shade(const t_vec3 *point, const t_scene *scene, __constant t_shape *shape)
{
	__constant t_material *material = get_material(scene, shape);
	t_color color = color_scalar(material->color, scene->config.ambient);
	__constant t_byte *light_ptr = scene->lightsourcebuffer;
	int i = -1;
	const t_fragment fragment = compose_fragment(scene, point, shape);
	while (++i < scene->meta.nlightsources)
	{
		__constant t_lightsource *light = (__constant t_lightsource*)light_ptr;
		// TODO: add soft shadows
		//color = color_add(color, color_scalar(illuminate(light_ptr, &fragment), 1.0f - dimness(point, scene, light_ptr)));
		color = color_add(color, illuminate(light_ptr, &fragment));
		if (light->lightsource_type == POINTLIGHT)
			light_ptr += sizeof(t_lightsource) + sizeof(t_pointlightsource);
		else if (light->lightsource_type == DIRLIGHT)
			light_ptr += sizeof(t_lightsource) + sizeof(t_dirlightsource);
		else if (light->lightsource_type == SPOTLIGHT)
			light_ptr += sizeof(t_lightsource) + sizeof(t_spotlightsource);
	}
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"
#include "scene.h"
#include <SDL.h>
#include <math.h>
#include "gui.h"

static t_ray	obtain_camera_ray(const t_scene *scene, int x, int y)
{
	t_ray	camera_ray;
	t_mat4d	orientation;
	t_vec4d	direction;
	float	fov;

	fov = tan(scene->config.fov / 2.0f * M_PI / 180.0f);
	camera_ray.origin = opencl_vec4_to_vec3(scene->camera.position);
	direction = (t_vec4d){
		(2.0f * ((x + 0.5f) / (SCENE_WIDTH - 2.0f * SCENE_PADDING)) - 1.0f)
		* fov * ((SCENE_WIDTH - 2.0f * SCENE_PADDING) / (float)(SCENE_HEIGHT - 2.0f * SCENE_PADDING)),
		(1.0f - 2.0f * ((y + 0.5f) / (SCENE_HEIGHT - 2.0f * SCENE_PADDING))) * fov, -1.0f, 0.0f};
	direction = vec4d_normalize(&direction);
	orientation = opencl_mat4x4_to_mat4x4(scene->camera.rotation_matrix);
	direction = mat4d_vec4d_mult(&orientation, &direction);
	camera_ray.direction = (t_vec3d){direction.x, direction.y, direction.z};
	return (camera_ray);
}

const t_shape	*pick_shape(const SDL_MouseButtonEvent *event, t_scene *scene)
{
	t_ray			ray;
	const t_shape	*shape;
	float			t;

	shape = NULL;
	if (event->x > (SCENE_X + SCENE_PADDING)
	&& event->x < (SCENE_X + SCENE_WIDTH - SCENE_PADDING)
	&& event->y > (SCENE_Y + SCENE_PADDING)
	&& event->y < (SCENE_Y + SCENE_HEIGHT - SCENE_PADDING))
	{
		ray = obtain_camera_ray(scene, event->x - (SCENE_X + SCENE_PADDING),
		event->y - (SCENE_Y + SCENE_PADDING));
		shape = cast_ray(scene, &ray, &t);
		if (shape != NULL)
			select_object(shape->addr);
	}
	return (shape);
}

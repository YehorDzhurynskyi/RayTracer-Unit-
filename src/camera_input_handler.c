/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_input_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_opengl.h>
#include "renderer.h"

void	camera_key_handler(const SDL_Event *event)
{
	t_vec3d	forward;
	t_vec3d	right;
	float	forward_speed;
	float	side_speed;

	if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_s
	|| event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_d)
	{
		forward_speed = 0.0f;
		side_speed = 0.0f;
		if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_s)
		{
			forward.x = -g_scene_renderer.scene.camera.rotation_matrix.s2;
			forward.y = -g_scene_renderer.scene.camera.rotation_matrix.s6;
			forward.z = -g_scene_renderer.scene.camera.rotation_matrix.sa;
			forward_speed = event->key.keysym.sym == SDLK_w ? 0.2f : -0.2f;
		}
		if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_d)
		{
			right.x = g_scene_renderer.scene.camera.rotation_matrix.s0;
			right.y = g_scene_renderer.scene.camera.rotation_matrix.s4;
			right.z = g_scene_renderer.scene.camera.rotation_matrix.s8;
			side_speed = event->key.keysym.sym == SDLK_a ? -0.15f : 0.15f;
		}
		g_scene_renderer.scene.camera.position.x += forward_speed * forward.x + side_speed * right.x;
		g_scene_renderer.scene.camera.position.y += forward_speed * forward.y + side_speed * right.y;
		g_scene_renderer.scene.camera.position.z += forward_speed * forward.z + side_speed * right.z;
	}
}

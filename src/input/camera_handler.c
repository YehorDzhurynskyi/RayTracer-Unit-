/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "renderer.h"

void	camera_key_handler(t_camera *camera)
{
	t_vec3d		forward;
	t_vec3d		right;
	t_vec3d		up;
	float		forward_speed;
	float		side_speed;
	float		up_speed;
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S]
	|| keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D]
	|| keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
	{
		forward_speed = 0.0f;
		side_speed = 0.0f;
		up_speed = 0.0f;
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S])
		{
			forward.x = -camera->rotation_matrix.s2;
			forward.y = -camera->rotation_matrix.s6;
			forward.z = -camera->rotation_matrix.sa;
			forward_speed = keystate[SDL_SCANCODE_W] ? 0.2f : -0.2f;
		}
		if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D])
		{
			right.x = camera->rotation_matrix.s0;
			right.y = camera->rotation_matrix.s4;
			right.z = camera->rotation_matrix.s8;
			side_speed = keystate[SDL_SCANCODE_A] ? -0.15f : 0.15f;
		}
		if (keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
		{
			up.x = camera->rotation_matrix.s1;
			up.y = camera->rotation_matrix.s5;
			up.z = camera->rotation_matrix.s9;
			up_speed = keystate[SDL_SCANCODE_Q] ? -0.15f : 0.15f;
		}
		camera->position.x += forward_speed * forward.x + side_speed * right.x + up_speed * up.x;
		camera->position.y += forward_speed * forward.y + side_speed * right.y + up_speed * up.y;
		camera->position.z += forward_speed * forward.z + side_speed * right.z + up_speed * up.z;
	}
}

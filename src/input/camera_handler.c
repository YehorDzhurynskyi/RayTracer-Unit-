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
	float		forward_speed;
	float		side_speed;
	const Uint8	*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S]
	|| keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D])
	{
		forward_speed = 0.0f;
		side_speed = 0.0f;
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
		camera->position.x += forward_speed * forward.x + side_speed * right.x;
		camera->position.y += forward_speed * forward.y + side_speed * right.y;
		camera->position.z += forward_speed * forward.z + side_speed * right.z;
	}
}

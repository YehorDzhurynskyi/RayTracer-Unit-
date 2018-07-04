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
#include <math.h>

#define CAM_SPEED		0.3
#define CAM_ROT_SPEED	1.5

static t_vec3d		rodrigoues_rotation(const t_vec3d *v,
const t_vec3d *n, const double angle)
{
	t_vec3d a;
	t_vec3d b;
	t_vec3d c;

	a = vec3d_scalar(n, vec3d_dot(v, n) * (1.0 - cos(angle)));
	b = vec3d_scalar(v, cos(angle));
	c = vec3d_cross(n, v);
	c = vec3d_scalar(&c, sin(angle));
	a = vec3d_add(&a, &b);
	return (vec3d_add(&a, &c));
}

static t_clmat4x4	camera_rotate(const Uint8 *keystate, t_vec3d *forward,
t_vec3d *right, t_vec3d *up)
{
	double	angle;

	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN])
	{
		angle = CAM_ROT_SPEED * M_PI / 180.0;
		angle = keystate[SDL_SCANCODE_UP] ? angle : -angle;
		*up = rodrigoues_rotation(up, right, angle);
		*forward = rodrigoues_rotation(forward, right, angle);
	}
	if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT])
	{
		angle = CAM_ROT_SPEED * M_PI / 180.0;
		angle = keystate[SDL_SCANCODE_LEFT] ? angle : -angle;
		*right = rodrigoues_rotation(right, up, angle);
		*forward = rodrigoues_rotation(forward, up, angle);
	}
	if (keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
	{
		angle = CAM_ROT_SPEED * M_PI / 180.0;
		angle = keystate[SDL_SCANCODE_E] ? angle : -angle;
		*up = rodrigoues_rotation(up, forward, angle);
		*right = rodrigoues_rotation(right, forward, angle);
	}
	return (camera_rotation_matrix(forward, right, up));
}

static t_vec3d		camera_translate(const Uint8 *keystate,
const t_vec3d *forward, const t_vec3d *right)
{
	t_vec3d	speed;

	speed = (t_vec3d){0.0, 0.0, 0.0};
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S])
		speed.z = keystate[SDL_SCANCODE_W] ? CAM_SPEED : -CAM_SPEED;
	if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D])
		speed.x = keystate[SDL_SCANCODE_A] ? -CAM_SPEED : CAM_SPEED;
	return ((t_vec3d){speed.z * forward->x + speed.x * right->x,
	speed.z * forward->y + speed.x * right->y,
	speed.z * forward->z + speed.x * right->z});
}

void				camera_key_handler(t_camera *cam)
{
	const Uint8	*keystate;
	t_vec3d		translation;
	t_vec3d		right;
	t_vec3d		up;
	t_vec3d		forward;

	keystate = SDL_GetKeyboardState(NULL);
	right = (t_vec3d){cam->rotation_matrix.s0, cam->rotation_matrix.s4,
	cam->rotation_matrix.s8};
	up = (t_vec3d){cam->rotation_matrix.s1, cam->rotation_matrix.s5,
	cam->rotation_matrix.s9};
	forward = (t_vec3d){-cam->rotation_matrix.s2, -cam->rotation_matrix.s6,
	-cam->rotation_matrix.sa};
	if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN]
	|| keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT]
	|| keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_E])
		cam->rotation_matrix = camera_rotate(keystate, &forward, &right, &up);
	if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S]
	|| keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D])
	{
		translation = camera_translate(keystate, &forward, &right);
		cam->position.x += translation.x;
		cam->position.y += translation.y;
		cam->position.z += translation.z;
	}
}

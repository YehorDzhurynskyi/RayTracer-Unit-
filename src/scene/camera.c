/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static inline void	camera_set_rotation_matrix(t_camera *camera,
const t_vec3d *forward, const t_vec3d *right, const t_vec3d *up)
{
	camera->rotation_matrix.s0 = right->x;
	camera->rotation_matrix.s4 = right->y;
	camera->rotation_matrix.s8 = right->z;
	camera->rotation_matrix.sc = 0.0;
	camera->rotation_matrix.s1 = up->x;
	camera->rotation_matrix.s5 = up->y;
	camera->rotation_matrix.s9 = up->z;
	camera->rotation_matrix.sd = 0.0;
	camera->rotation_matrix.s2 = -forward->x;
	camera->rotation_matrix.s6 = -forward->y;
	camera->rotation_matrix.sa = -forward->z;
	camera->rotation_matrix.se = 0.0;
	camera->rotation_matrix.s3 = 0.0;
	camera->rotation_matrix.s7 = 0.0;
	camera->rotation_matrix.sb = 0.0;
	camera->rotation_matrix.sf = 0.0;
}

t_camera			camera_look_at(const t_vec3d *position,
const t_vec3d *spot, const t_vec3d *up)
{
	t_camera	camera;
	t_vec3d		forward;
	t_vec3d		right;
	t_vec3d		nup;

	camera.position = (t_clvec4){{position->x, position->y, position->z, 0.0f}};
	nup = vec3d_normalize(up);
	forward = vec3d_sub(spot, position);
	forward = vec3d_normalize(&forward);
	right = vec3d_cross(&forward, &nup);
	right = vec3d_normalize(&right);
	nup = vec3d_cross(&right, &forward);
	nup = vec3d_normalize(&nup);
	camera_set_rotation_matrix(&camera, &forward, &right, &nup);
	return (camera);
}

t_camera			camera_create(const t_vec3d *position,
const t_vec3d *forward, const t_vec3d *right, const t_vec3d *up)
{
	t_camera	camera;

	camera.position.x = position->x;
	camera.position.y = position->y;
	camera.position.z = position->z;
	camera.position.w = 0.0;
	camera_set_rotation_matrix(&camera, forward, right, up);
	return (camera);
}

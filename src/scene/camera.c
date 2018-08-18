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

t_clmat4x4	camera_rotation_matrix(const t_vec3d *forward,
const t_vec3d *right, const t_vec3d *up)
{
	t_clmat4x4	rotation_matrix;

	rotation_matrix.s0 = right->x;
	rotation_matrix.s4 = right->y;
	rotation_matrix.s8 = right->z;
	rotation_matrix.sc = 0.0;
	rotation_matrix.s1 = up->x;
	rotation_matrix.s5 = up->y;
	rotation_matrix.s9 = up->z;
	rotation_matrix.sd = 0.0;
	rotation_matrix.s2 = -forward->x;
	rotation_matrix.s6 = -forward->y;
	rotation_matrix.sa = -forward->z;
	rotation_matrix.se = 0.0;
	rotation_matrix.s3 = 0.0;
	rotation_matrix.s7 = 0.0;
	rotation_matrix.sb = 0.0;
	rotation_matrix.sf = 0.0;
	return (rotation_matrix);
}

t_camera	camera_look_at(const t_vec3d *position,
const t_vec3d *spot, const t_vec3d *up)
{
	t_camera	camera;
	t_vec3d		forward;
	t_vec3d		right;
	t_vec3d		nup;

	camera.position = (t_clvec3){{position->x, position->y, position->z}};
	nup = vec3d_normalize(up);
	forward = vec3d_sub(spot, position);
	forward = vec3d_normalize(&forward);
	right = vec3d_cross(&forward, &nup);
	right = vec3d_normalize(&right);
	nup = vec3d_cross(&right, &forward);
	nup = vec3d_normalize(&nup);
	camera.rotation_matrix = camera_rotation_matrix(&forward, &right, &nup);
	return (camera);
}

t_camera	camera_create(const t_vec3d *position,
const t_vec3d *forward, const t_vec3d *right, const t_vec3d *up)
{
	t_camera	camera;

	camera.position.x = position->x;
	camera.position.y = position->y;
	camera.position.z = position->z;
	camera.rotation_matrix = camera_rotation_matrix(forward, right, up);
	return (camera);
}

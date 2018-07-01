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

#include "scenerepository.h"

static t_camera	deserialize_look_at(const t_vec3d *position,
const t_cson *cson, const t_vec3d *up, t_err_code *err)
{
	t_vec3d	spot;

	spot = deserialize_vec3d(cson, CSON_SPOT_KEY, RT_VEC_REPO_REQUIRED, err);
	return (camera_look_at(position, &spot, up));
}

static t_camera	deserialize_rotation_matrix(const t_cson *cson,
const t_vec3d *position, const t_vec3d *up, t_err_code *err)
{
	t_vec3d	forward;
	t_vec3d	right;

	forward = deserialize_vec3d(cson, CSON_FORWARD_KEY,
	RT_VEC_REPO_REQUIRED | RT_VEC_REPO_NORMALIZE, err);
	right = deserialize_vec3d(cson, CSON_RIGHT_KEY,
	RT_VEC_REPO_REQUIRED | RT_VEC_REPO_NORMALIZE, err);
	return (camera_create(position, &forward, &right, up));
}

t_camera		deserialize_camera(const t_cson *cson, t_err_code *err)
{
	t_vec3d	position;
	t_vec3d	up;

	position = deserialize_vec3d(cson, CSON_POSITION_KEY, RT_VEC_REPO_REQUIRED, err);
	up = deserialize_vec3d(cson, CSON_UP_KEY,
	RT_VEC_REPO_NORMALIZE | RT_VEC_REPO_REQUIRED, err);
	if (cson_valueof(cson, CSON_SPOT_KEY) != NULL)
		return (deserialize_look_at(&position, cson, &up, err));
	else
		return (deserialize_rotation_matrix(cson, &position, &up, err));
}

t_cson			*serialize_camera(const t_camera *camera)
{
	t_cson		*cson;
	t_clvec3	vec;

	cson = cson_object();
	vec = camera->position;
	cson_put(cson, CSON_POSITION_KEY, serialize_vec3(&vec));
	vec = (t_clvec3){{camera->rotation_matrix.s0,
	camera->rotation_matrix.s1, camera->rotation_matrix.s3}};
	cson_put(cson, CSON_RIGHT_KEY, serialize_vec3(&vec));
	vec = (t_clvec3){{camera->rotation_matrix.s4,
	camera->rotation_matrix.s5, camera->rotation_matrix.s6}};
	cson_put(cson, CSON_UP_KEY, serialize_vec3(&vec));
	vec = (t_clvec3){{-camera->rotation_matrix.s8,
	-camera->rotation_matrix.s9, -camera->rotation_matrix.sa}};
	cson_put(cson, CSON_FORWARD_KEY, serialize_vec3(&vec));
	return (cson);
}

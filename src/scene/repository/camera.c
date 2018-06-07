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

t_camera	deserialize_camera(const t_cson *cson)
{
	t_vec3d	position;
	t_vec3d	forward;
	t_vec3d	right;
	t_vec3d	up;
	t_vec3d	spot;

	position = deserialize_vec3d(cson_valueof(cson, CSON_POSITION_KEY), FALSE);
	right = deserialize_vec3d(cson_valueof(cson, CSON_RIGHT_KEY), TRUE);
	up = deserialize_vec3d(cson_valueof(cson, CSON_UP_KEY), TRUE);
	forward = deserialize_vec3d(cson_valueof(cson, CSON_FORWARD_KEY), TRUE);
	spot = deserialize_vec3d(cson_valueof(cson, CSON_SPOT_KEY), FALSE);
	return (camera_look_at(&position, &spot, &up));
}

t_cson		*serialize_camera(const t_camera *camera)
{
	t_cson		*cson;
	t_vec3d		vec;
	t_clvec4	position;

	cson = cson_object();
	position = camera->position;
	cson_put(cson, CSON_POSITION_KEY, serialize_vec4(&position));
	vec = (t_vec3d){camera->rotation_matrix.s0,
	camera->rotation_matrix.s1, camera->rotation_matrix.s3};
	cson_put(cson, CSON_RIGHT_KEY, serialize_vec3d(&vec));
	vec = (t_vec3d){camera->rotation_matrix.s4,
	camera->rotation_matrix.s5, camera->rotation_matrix.s6};
	cson_put(cson, CSON_UP_KEY, serialize_vec3d(&vec));
	vec = (t_vec3d){-camera->rotation_matrix.s8,
	-camera->rotation_matrix.s9, -camera->rotation_matrix.sa};
	cson_put(cson, CSON_FORWARD_KEY, serialize_vec3d(&vec));
	return (cson);
}

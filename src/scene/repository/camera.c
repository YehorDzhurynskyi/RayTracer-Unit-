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
const t_cson *spot_cson, const t_vec3d *up, t_err_code *err)
{
	t_vec3d	spot;

	spot = deserialize_vec3d(spot_cson, FALSE, err);
	return (camera_look_at(position, &spot, up));
}

static t_camera	deserialize_rotation_matrix(const t_cson *cson,
const t_vec3d *position, const t_vec3d *up, t_err_code *err)
{
	t_vec3d			forward;
	t_vec3d			right;
	const t_cson	*forward_cson;
	const t_cson	*right_cson;

	forward_cson = cson_valueof(cson, CSON_FORWARD_KEY);
	right_cson = cson_valueof(cson, CSON_RIGHT_KEY);
	if (forward_cson == NULL || right_cson == NULL)
	{ // TODO: print error message
		*err = RT_NO_REQUIRED_VALUE_ERROR;
		return ((t_camera){});
	}
	forward = deserialize_vec3d(forward_cson, TRUE, err);
	right = deserialize_vec3d(right_cson, TRUE, err);
	return (camera_create(position, &forward, &right, up));
}

t_camera		deserialize_camera(const t_cson *cson, t_err_code *err)
{
	t_vec3d			position;
	t_vec3d			up;
	const t_cson	*position_cson;
	const t_cson	*up_cson;
	const t_cson	*spot_cson;

	position_cson = cson_valueof(cson, CSON_POSITION_KEY);
	up_cson = cson_valueof(cson, CSON_UP_KEY);
	if (position_cson == NULL || up_cson == NULL)
	{ // TODO: print error message
		*err = RT_NO_REQUIRED_VALUE_ERROR;
		return ((t_camera){});
	}
	position = deserialize_vec3d(position_cson, FALSE, err);
	up = deserialize_vec3d(up_cson, TRUE, err);
	spot_cson = cson_valueof(cson, CSON_SPOT_KEY);
	if (spot_cson != NULL)
		return (deserialize_look_at(&position, spot_cson, &up, err));
	else
		return (deserialize_rotation_matrix(cson, &position, &up, err));
}

t_cson			*serialize_camera(const t_camera *camera)
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

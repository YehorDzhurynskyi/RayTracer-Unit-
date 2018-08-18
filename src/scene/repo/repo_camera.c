/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

static t_camera	deserialize_look_at(const t_vec3d *position,
const t_cson *cson, const t_vec3d *up)
{
	t_vec3d	spot;

	spot = deserialize_vec3d_required(cson_valueof(cson, CSON_SPOT_KEY), FALSE);
	return (camera_look_at(position, &spot, up));
}

static t_camera	deserialize_rotation_matrix(const t_cson *cson,
const t_vec3d *position, const t_vec3d *up)
{
	t_vec3d	forward;
	t_vec3d	right;

	forward = deserialize_vec3d_required(cson_valueof(cson,
	CSON_FORWARD_KEY), TRUE);
	right = deserialize_vec3d_required(cson_valueof(cson,
	CSON_RIGHT_KEY), TRUE);
	return (camera_create(position, &forward, &right, up));
}

t_camera		deserialize_camera(const t_cson *cson)
{
	t_vec3d	position;
	t_vec3d	up;

	position = deserialize_vec3d_required(cson_valueof(cson,
	CSON_POSITION_KEY), FALSE);
	up = deserialize_vec3d_required(cson_valueof(cson, CSON_UP_KEY), TRUE);
	if (cson_valueof(cson, CSON_SPOT_KEY) != NULL)
		return (deserialize_look_at(&position, cson, &up));
	else
		return (deserialize_rotation_matrix(cson, &position, &up));
}

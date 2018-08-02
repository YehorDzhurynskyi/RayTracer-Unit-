/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include <math.h>

static inline t_clmat4x4	orientation_matrix(const t_clscalar *r)
{
	t_clmat4x4	orientation;

	orientation.s0 = r[5] * r[3];
	orientation.s1 = -r[4] * r[1] + r[5] * r[2] * r[0];
	orientation.s2 = r[4] * r[0] + r[5] * r[2] * r[1];
	orientation.s3 = 0.0;
	orientation.s4 = r[4] * r[3];
	orientation.s5 = r[5] * r[1] + r[4] * r[2] * r[0];
	orientation.s6 = -r[5] * r[0] + r[4] * r[2] * r[1];
	orientation.s7 = 0.0;
	orientation.s8 = -r[2];
	orientation.s9 = r[3] * r[0];
	orientation.sa = r[3] * r[1];
	orientation.sb = 0.0;
	orientation.sc = 0.0;
	orientation.sd = 0.0;
	orientation.se = 0.0;
	orientation.sf = 1.0;
	return (orientation);
}

t_clmat4x4	to_orientation_matrix(float rx, float ry, float rz)
{
	t_clscalar	r[6];

	rx *= M_PI / 180.0;
	ry *= M_PI / 180.0;
	rz *= M_PI / 180.0;
	r[0] = sin(rx);
	r[1] = cos(rx);
	r[2] = sin(ry);
	r[3] = cos(ry);
	r[4] = sin(rz);
	r[5] = cos(rz);
	return (orientation_matrix(r));
}

t_clmat4x4	deserialize_orientation_required(const t_cson *cson)
{
	t_clvec3	rotation;

	rotation = deserialize_vec3_required(cson_valueof(cson, CSON_ORIENTATION_KEY), FALSE);
	return (to_orientation_matrix(rotation.x, rotation.y, rotation.z));
}

t_clmat4x4	deserialize_orientation_optional(const t_cson *cson, const t_vec3d default_angles)
{
	t_clvec3	rotation;

	rotation = deserialize_vec3_optional(cson_valueof(cson, CSON_ORIENTATION_KEY), FALSE, default_angles);
	return (to_orientation_matrix(rotation.x, rotation.y, rotation.z));
}

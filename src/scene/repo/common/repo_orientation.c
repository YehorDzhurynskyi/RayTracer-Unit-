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

t_clmat4x4	to_matrix(t_clvec3 rotation)
{
	t_clscalar	r[6];

	rotation.x *= M_PI / 180.0;
	rotation.y *= M_PI / 180.0;
	rotation.z *= M_PI / 180.0;
	r[0] = sin(rotation.x);
	r[1] = cos(rotation.x);
	r[2] = sin(rotation.y);
	r[3] = cos(rotation.y);
	r[4] = sin(rotation.z);
	r[5] = cos(rotation.z);
	return (orientation_matrix(r));
}

t_clmat4x4	deserialize_orientation_required(const t_cson *cson)
{
	return (to_matrix(deserialize_vec3_required(cson_valueof(cson, CSON_ORIENTATION_KEY), FALSE)));
}

t_clmat4x4	deserialize_orientation_optional(const t_cson *cson, const t_vec3d default_angles)
{
	return (to_matrix(deserialize_vec3_optional(cson_valueof(cson, CSON_ORIENTATION_KEY), FALSE, default_angles)));
}

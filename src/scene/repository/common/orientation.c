/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
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

t_clmat4x4	deserialize_orientation(const t_cson *cson, int mask, t_err_code *err)
{
	t_clvec3	rotation;
	t_clscalar	r[6];

	rotation = deserialize_vec3(cson, CSON_ORIENTATION_KEY, mask, err);
	if (*err == RT_NO_OPTIONAL_VALUE_ERROR)
	{
		rotation = (t_clvec3){{0.0, 0.0, 0.0}};
		*err = RT_NO_ERROR;
	}
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

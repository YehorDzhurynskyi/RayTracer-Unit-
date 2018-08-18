/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_adapter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"

inline t_vec3d	opencl_vec3_to_vec3(t_clvec3 vec)
{
	return ((t_vec3d){vec.x, vec.y, vec.z});
}

inline t_vec4d	opencl_vec4_to_vec4(t_clvec4 vec)
{
	return ((t_vec4d){vec.x, vec.y, vec.z, vec.w});
}

inline t_vec3d	opencl_vec4_to_vec3(t_clvec4 vec)
{
	return ((t_vec3d){vec.x, vec.y, vec.z});
}

inline t_mat4d	opencl_mat4x4_to_mat4x4(t_clmat4x4 mat)
{
	t_mat4d	res;

	res.data[0][0] = mat.s0;
	res.data[0][1] = mat.s1;
	res.data[0][2] = mat.s2;
	res.data[0][3] = mat.s3;
	res.data[1][0] = mat.s4;
	res.data[1][1] = mat.s5;
	res.data[1][2] = mat.s6;
	res.data[1][3] = mat.s7;
	res.data[2][0] = mat.s8;
	res.data[2][1] = mat.s9;
	res.data[2][2] = mat.sa;
	res.data[2][3] = mat.sb;
	res.data[3][0] = mat.sc;
	res.data[3][1] = mat.sd;
	res.data[3][2] = mat.se;
	res.data[3][3] = mat.sf;
	return (res);
}

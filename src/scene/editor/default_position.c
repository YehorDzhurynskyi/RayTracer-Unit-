/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_vec3d	scenebuffer_default_position(void)
{
	t_vec3d	forward;
	t_vec3d	position;

	forward = (t_vec3d){-g_main_scene.camera.rotation_matrix.s2, -g_main_scene.camera.rotation_matrix.s6,
	-g_main_scene.camera.rotation_matrix.sa};
	position = opencl_vec4_to_vec3(g_main_scene.camera.position);
	forward = vec3d_scalar(&forward, 4.0f);
	return (vec3d_add(&position, &forward));
}

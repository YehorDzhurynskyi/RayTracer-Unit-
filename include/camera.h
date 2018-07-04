/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "opencl.h"
# include "ft.h"

typedef struct		__attribute__ ((packed)) s_camera
{
	t_clmat4x4		rotation_matrix;
	t_clvec4		position;
}	t_camera;

t_camera			camera_look_at(const t_vec3d *position,
const t_vec3d *spot, const t_vec3d *up);
t_camera			camera_create(const t_vec3d *position,
const t_vec3d *forward, const t_vec3d *right, const t_vec3d *up);
t_clmat4x4			camera_rotation_matrix(const t_vec3d *forward,
const t_vec3d *right, const t_vec3d *up);

#endif

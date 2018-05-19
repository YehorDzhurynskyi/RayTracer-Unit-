/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_vec_mult.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:10:06 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:58:09 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"

inline t_vec3f	mat3f_vec3f_mult(const t_mat3f *m, const t_vec3f *v)
{
	return ((t_vec3f){
		m->data[0][0] * v->x + m->data[0][1] * v->y + m->data[0][2] * v->z,
		m->data[1][0] * v->x + m->data[1][1] * v->y + m->data[1][2] * v->z,
		m->data[2][0] * v->x + m->data[2][1] * v->y + m->data[2][2] * v->z});
}

inline t_vec3d	mat3d_vec3d_mult(const t_mat3d *m, const t_vec3d *v)
{
	return ((t_vec3d){
		m->data[0][0] * v->x + m->data[0][1] * v->y + m->data[0][2] * v->z,
		m->data[1][0] * v->x + m->data[1][1] * v->y + m->data[1][2] * v->z,
		m->data[2][0] * v->x + m->data[2][1] * v->y + m->data[2][2] * v->z});
}

inline t_vec4f	mat4f_vec4f_mult(const t_mat4f *m, const t_vec4f *v)
{
	return ((t_vec4f){
		m->data[0][0] * v->x + m->data[0][1] * v->y
		+ m->data[0][2] * v->z + m->data[0][3] * v->w,
		m->data[1][0] * v->x + m->data[1][1] * v->y
		+ m->data[1][2] * v->z + m->data[1][3] * v->w,
		m->data[2][0] * v->x + m->data[2][1] * v->y
		+ m->data[2][2] * v->z + m->data[2][3] * v->w,
		m->data[3][0] * v->x + m->data[3][1] * v->y
		+ m->data[3][2] * v->z + m->data[3][3] * v->w});
}

inline t_vec4d	mat4d_vec4d_mult(const t_mat4d *m, const t_vec4d *v)
{
	return ((t_vec4d){
		m->data[0][0] * v->x + m->data[0][1] * v->y
		+ m->data[0][2] * v->z + m->data[0][3] * v->w,
		m->data[1][0] * v->x + m->data[1][1] * v->y
		+ m->data[1][2] * v->z + m->data[1][3] * v->w,
		m->data[2][0] * v->x + m->data[2][1] * v->y
		+ m->data[2][2] * v->z + m->data[2][3] * v->w,
		m->data[3][0] * v->x + m->data[3][1] * v->y
		+ m->data[3][2] * v->z + m->data[3][3] * v->w});
}

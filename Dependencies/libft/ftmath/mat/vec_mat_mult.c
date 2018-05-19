/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mat_mult.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:10:06 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:58:09 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"

inline t_vec3f	vec3f_mat3f_mult(const t_vec3f *v, const t_mat3f *m)
{
	return ((t_vec3f){
		m->data[0][0] * v->x + m->data[1][0] * v->y + m->data[2][0] * v->z,
		m->data[0][1] * v->x + m->data[1][1] * v->y + m->data[2][1] * v->z,
		m->data[0][2] * v->x + m->data[1][2] * v->y + m->data[2][2] * v->z});
}

inline t_vec3d	vec3d_mat3d_mult(const t_vec3d *v, const t_mat3d *m)
{
	return ((t_vec3d){
		m->data[0][0] * v->x + m->data[1][0] * v->y + m->data[2][0] * v->z,
		m->data[0][1] * v->x + m->data[1][1] * v->y + m->data[2][1] * v->z,
		m->data[0][2] * v->x + m->data[1][2] * v->y + m->data[2][2] * v->z});
}

inline t_vec4f	vec4f_mat4f_mult(const t_vec4f *v, const t_mat4f *m)
{
	return ((t_vec4f){
		m->data[0][0] * v->x + m->data[1][0] * v->y
		+ m->data[2][0] * v->z + m->data[3][0] * v->w,
		m->data[0][1] * v->x + m->data[1][1] * v->y
		+ m->data[2][1] * v->z + m->data[3][1] * v->w,
		m->data[0][2] * v->x + m->data[1][2] * v->y
		+ m->data[2][2] * v->z + m->data[3][2] * v->w,
		m->data[0][3] * v->x + m->data[1][3] * v->y
		+ m->data[2][3] * v->z + m->data[3][3] * v->w});
}

inline t_vec4d	vec4d_mat4d_mult(const t_vec4d *v, const t_mat4d *m)
{
	return ((t_vec4d){
		m->data[0][0] * v->x + m->data[1][0] * v->y
		+ m->data[2][0] * v->z + m->data[3][0] * v->w,
		m->data[0][1] * v->x + m->data[1][1] * v->y
		+ m->data[2][1] * v->z + m->data[3][1] * v->w,
		m->data[0][2] * v->x + m->data[1][2] * v->y
		+ m->data[2][2] * v->z + m->data[3][2] * v->w,
		m->data[0][3] * v->x + m->data[1][3] * v->y
		+ m->data[2][3] * v->z + m->data[3][3] * v->w});
}

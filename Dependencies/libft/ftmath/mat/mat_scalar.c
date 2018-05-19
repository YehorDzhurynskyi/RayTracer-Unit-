/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_scalar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:40:58 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/21 15:49:23 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"

inline t_mat3f	mat3f_scalar(const t_mat3f *m, float s)
{
	int		i;
	t_mat3f	res;

	i = -1;
	while (++i < 9)
		res.data[i % 3][i / 3] = m->data[i % 3][i / 3] * s;
	return (res);
}

inline t_mat3d	mat3d_scalar(const t_mat3d *m, double s)
{
	int		i;
	t_mat3d	res;

	i = -1;
	while (++i < 9)
		res.data[i % 3][i / 3] = m->data[i % 3][i / 3] * s;
	return (res);
}

inline t_mat4f	mat4f_scalar(const t_mat4f *m, float s)
{
	int		i;
	t_mat4f	res;

	i = -1;
	while (++i < 16)
		res.data[i % 4][i / 4] = m->data[i % 4][i / 4] * s;
	return (res);
}

inline t_mat4d	mat4d_scalar(const t_mat4d *m, double s)
{
	int		i;
	t_mat4d	res;

	i = -1;
	while (++i < 16)
		res.data[i % 4][i / 4] = m->data[i % 4][i / 4] * s;
	return (res);
}

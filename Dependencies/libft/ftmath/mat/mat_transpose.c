/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_transpose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"

inline t_mat3f	mat3f_transpose(const t_mat3f *m)
{
	t_mat3f	res;
	int		i;

	i = -1;
	while (++i < 9)
		res.data[i % 3][i / 3] = m->data[i / 3][i % 3];
	return (res);
}

inline t_mat3d	mat3d_transpose(const t_mat3d *m)
{
	t_mat3d	res;
	int		i;

	i = -1;
	while (++i < 9)
		res.data[i % 3][i / 3] = m->data[i / 3][i % 3];
	return (res);
}

inline t_mat4f	mat4f_transpose(const t_mat4f *m)
{
	t_mat4f	res;
	int		i;

	i = -1;
	while (++i < 16)
		res.data[i % 4][i / 4] = m->data[i / 4][i % 4];
	return (res);
}

inline t_mat4d	mat4d_transpose(const t_mat4d *m)
{
	t_mat4d	res;
	int		i;

	i = -1;
	while (++i < 16)
		res.data[i % 4][i / 4] = m->data[i / 4][i % 4];
	return (res);
}

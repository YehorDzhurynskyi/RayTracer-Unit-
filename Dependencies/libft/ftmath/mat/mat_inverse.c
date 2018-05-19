/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:40:58 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/21 15:49:23 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"
#include "ft.h"

inline t_mat3f	mat3f_inverse(const t_mat3f *m)
{
	float	d;
	t_mat3f	res;
	int		i;
	int		j;
	float	minor[2][2];

	d = mat3f_determinant(m->data);
	if (d == 0.0f)
		return (*m);
	d = 1.0f / d;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			mat3f_minor(minor, m->data, i, j);
			res.data[j][i] = d * (minor[0][0] * minor[1][1]
			- minor[0][1] * minor[1][0]);
			res.data[j][i] = (i + j) % 2 == 1
			? -res.data[j][i] : res.data[j][i];
		}
	}
	return (res);
}

inline t_mat3d	mat3d_inverse(const t_mat3d *m)
{
	double	d;
	t_mat3d	res;
	int		i;
	int		j;
	double	minor[2][2];

	d = mat3d_determinant(m->data);
	if (d == 0.0)
		return (*m);
	d = 1.0 / d;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			mat3d_minor(minor, m->data, i, j);
			res.data[j][i] = d * (minor[0][0] * minor[1][1]
			- minor[0][1] * minor[1][0]);
			res.data[j][i] = (i + j) % 2 == 1
			? -res.data[j][i] : res.data[j][i];
		}
	}
	return (res);
}

inline t_mat4f	mat4f_inverse(const t_mat4f *m)
{
	float	d;
	t_mat4f	res;
	int		i;
	int		j;
	float	minor[3][3];

	d = mat4f_determinant(m->data);
	if (d == 0.0f)
		return (*m);
	d = 1.0f / d;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			mat4f_minor(minor, m->data, i, j);
			res.data[j][i] = d * mat3f_determinant(minor);
			res.data[j][i] = (i + j) % 2 == 1
			? -res.data[j][i] : res.data[j][i];
		}
	}
	return (res);
}

inline t_mat4d	mat4d_inverse(const t_mat4d *m)
{
	double	d;
	t_mat4d	res;
	int		i;
	int		j;
	double	minor[3][3];

	d = mat4d_determinant(m->data);
	if (d == 0.0)
		return (*m);
	d = 1.0 / d;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			mat4d_minor(minor, m->data, i, j);
			res.data[j][i] = d * mat3d_determinant(minor);
			res.data[j][i] = (i + j) % 2 == 1
			? -res.data[j][i] : res.data[j][i];
		}
	}
	return (res);
}

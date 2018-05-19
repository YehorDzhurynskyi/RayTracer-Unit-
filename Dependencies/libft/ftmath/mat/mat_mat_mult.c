/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mat_mult.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:40:58 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/21 15:49:23 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"

inline t_mat3f	mat3f_mat3f_mult(const t_mat3f *m1, const t_mat3f *m2)
{
	t_mat3f	res;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res.data[i][j] = 0.0f;
			k = -1;
			while (++k < 3)
				res.data[i][j] += m1->data[i][k] * m2->data[k][j];
		}
	}
	return (res);
}

inline t_mat3d	mat3d_mat3d_mult(const t_mat3d *m1, const t_mat3d *m2)
{
	t_mat3d	res;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res.data[i][j] = 0.0;
			k = -1;
			while (++k < 3)
				res.data[i][j] += m1->data[i][k] * m2->data[k][j];
		}
	}
	return (res);
}

inline t_mat4f	mat4f_mat4f_mult(const t_mat4f *m1, const t_mat4f *m2)
{
	t_mat4f	res;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res.data[i][j] = 0.0f;
			k = -1;
			while (++k < 4)
				res.data[i][j] += m1->data[i][k] * m2->data[k][j];
		}
	}
	return (res);
}

inline t_mat4d	mat4d_mat4d_mult(const t_mat4d *m1, const t_mat4d *m2)
{
	t_mat4d	res;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res.data[i][j] = 0.0;
			k = -1;
			while (++k < 4)
				res.data[i][j] += m1->data[i][k] * m2->data[k][j];
		}
	}
	return (res);
}

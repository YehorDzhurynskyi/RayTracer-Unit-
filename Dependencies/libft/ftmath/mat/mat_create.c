/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"
#include "ft.h"

inline t_mat3f	mat3f_create(const float *data)
{
	t_mat3f	res;

	ft_memcpy(&res.data, data, sizeof(float) * 9);
	return (res);
}

inline t_mat3d	mat3d_create(const double *data)
{
	t_mat3d	res;

	ft_memcpy(&res.data, data, sizeof(double) * 9);
	return (res);
}

inline t_mat4f	mat4f_create(const float *data)
{
	t_mat4f	res;

	ft_memcpy(&res.data, data, sizeof(float) * 16);
	return (res);
}

inline t_mat4d	mat4d_create(const double *data)
{
	t_mat4d	res;

	ft_memcpy(&res.data, data, sizeof(double) * 16);
	return (res);
}

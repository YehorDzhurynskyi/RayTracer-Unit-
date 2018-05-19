/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "ft.h"

void	vec3f_print(const int fd, t_vec3f const *v)
{
	ft_printf_fd(fd, "vec3f: % 7.2f % 7.2f % 7.2f\n", v->x, v->y, v->z);
}

void	vec3d_print(const int fd, t_vec3d const *v)
{
	ft_printf_fd(fd, "vec3d: % 7.2f % 7.2f % 7.2f\n", v->x, v->y, v->z);
}

void	vec4f_print(const int fd, t_vec4f const *v)
{
	ft_printf_fd(fd, "vec4f: % 7.2f % 7.2f % 7.2f % 7.2f\n",
	v->x, v->y, v->z, v->w);
}

void	vec4d_print(const int fd, t_vec4d const *v)
{
	ft_printf_fd(fd, "vec4d: % 7.2f % 7.2f % 7.2f % 7.2f\n",
	v->x, v->y, v->z, v->w);
}

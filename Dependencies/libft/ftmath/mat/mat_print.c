/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:10:06 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:58:09 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"
#include "ft.h"

inline void	mat3f_print(const int fd, const t_mat3f *m)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		ft_printf_fd(fd, "% 7.2f % 7.2f % 7.2f\n",
		m->data[i][0], m->data[i][1], m->data[i][2]);
		i++;
	}
}

inline void	mat3d_print(const int fd, const t_mat3d *m)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		ft_printf_fd(fd, "% 7.2f % 7.2f % 7.2f\n",
		m->data[i][0], m->data[i][1], m->data[i][2]);
		i++;
	}
}

inline void	mat4f_print(const int fd, const t_mat4f *m)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		ft_printf_fd(fd, "% 7.2f % 7.2f % 7.2f % 7.2f\n",
		m->data[i][0], m->data[i][1], m->data[i][2], m->data[i][3]);
		i++;
	}
}

inline void	mat4d_print(const int fd, const t_mat4d *m)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		ft_printf_fd(fd, "% 7.2f % 7.2f % 7.2f % 7.2f\n",
		m->data[i][0], m->data[i][1], m->data[i][2], m->data[i][3]);
		i++;
	}
}

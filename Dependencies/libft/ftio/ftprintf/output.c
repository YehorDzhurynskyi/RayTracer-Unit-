/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern int	g_ftprintf_length;
extern int	g_ftprintf_fd;

void		print(const t_conversion *c,
const char *src, unsigned int size)
{
	if (c->minus_flag)
		buff_write(src, size);
	print_filler(c, size);
	if (!c->minus_flag)
		buff_write(src, size);
}

void		print_filler(const t_conversion *c, size_t size)
{
	unsigned int	i;
	char			filler;
	size_t			fsize;

	fsize = c->field_width;
	if (fsize < size)
		fsize = size;
	filler = c->zero_flag ? '0' : ' ';
	i = 0;
	while (i++ < fsize - size)
		buff_write(&filler, 1);
}

void		buff_write(const char *str, size_t size)
{
	ssize_t	ret;

	ret = write(g_ftprintf_fd, str, size);
	if (ret == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	g_ftprintf_length += ret;
}

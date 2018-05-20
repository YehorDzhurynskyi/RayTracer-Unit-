/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "text_manager.h"
#include "libft.h"
#include "output.h"
#include "number_manager.h"

extern int	g_ftprintf_length;

void		print_str(t_conversion *c,
const char *src, unsigned int size)
{
	if (!src)
	{
		src = "(null)";
		size = ft_strlen(src);
	}
	if (c->precision != -1)
		size = c->precision < (int)size ? (unsigned int)c->precision : size;
	print(c, src, size);
}

void		print_char(t_conversion *c, unsigned char ch)
{
	print(c, (char[]){ch}, 1);
}

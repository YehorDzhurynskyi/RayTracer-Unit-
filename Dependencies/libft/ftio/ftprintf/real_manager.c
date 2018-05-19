/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_manager.h"
#include "ft_float.h"
#include "output.h"

#define LNAN	"nan"
#define UNAN	"NAN"
#define LINF	"inf"
#define UINF	"INF"

extern char	g_nbuff[];

void		print_inf(t_bool is_neg, t_bool is_small, t_conversion *c)
{
	char	*off;

	if (c->zero_flag)
		c->zero_flag = FALSE;
	off = g_nbuff;
	if (is_neg)
	{
		*g_nbuff = '-';
		off++;
	}
	else
	{
		off++;
		if (c->space_flag)
			*g_nbuff = ' ';
		else if (c->plus_flag)
			*g_nbuff = '+';
		else
			off--;
	}
	ft_memcpy(off, is_small ? LINF : UINF, 3);
	print(c, g_nbuff, g_nbuff == off ? 3 : 4);
}

void		print_nan(t_bool is_small, t_conversion *c)
{
	if (c->zero_flag)
		c->zero_flag = FALSE;
	print(c, is_small ? LNAN : UNAN, 3);
}

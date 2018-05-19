/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "real_manager.h"
#include "number_manager.h"
#include "ft_float.h"

extern char		g_fracbuff[];
extern char		g_nbuff[];

t_nument		get_flreal(long double n, t_conversion *c)
{
	t_nument			ent;
	unsigned long long	integer;

	ent = (t_nument){0, 0, 0, 0, 0};
	integer = is_ldneg(n)
	? ~((unsigned long long)n) + 1 : (unsigned long long)n;
	ent.frac_len = c->precision;
	if (c->precision > 0)
		integer += ft_get_dfrac(g_fracbuff, c->precision, n);
	ent.int_len = fill_integer(g_nbuff, integer, c);
	return (ent);
}

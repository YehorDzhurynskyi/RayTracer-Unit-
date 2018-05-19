/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_neg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 12:30:36 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_float.h"

t_bool	is_finf(float f)
{
	uint32_t	b;

	b = *((uint32_t*)&f);
	return ((((b >> (FLT_MANT_DIG - 1)) & FT_FEXP) == FT_FEXP)
	&& ((b & FT_FMNT) == 0));
}

t_bool	is_dinf(double d)
{
	uint64_t	b;

	b = *((uint64_t*)&d);
	return ((((b >> (DBL_MANT_DIG - 1)) & FT_DEXP) == FT_DEXP)
	&& ((b & FT_DMNT) == 0));
}

t_bool	is_ldinf(long double ld)
{
	uint16_t	e;
	uint64_t	m;
	void		*p;

	p = &ld;
	e = *((uint16_t*)(p + 8));
	m = *((uint64_t*)p);
	return (((e & FT_LDEXP) == FT_LDEXP)
	&& ((m & FT_LDMNT) == 0));
}

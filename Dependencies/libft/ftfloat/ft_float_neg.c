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

t_bool	is_fneg(float f)
{
	uint8_t	b;
	void	*p;

	p = &f;
	b = *((uint8_t*)(p + 3));
	return ((b & 0x80) == 0x80);
}

t_bool	is_dneg(double d)
{
	uint8_t	b;
	void	*p;

	p = &d;
	b = *((uint8_t*)(p + 7));
	return ((b & 0x80) == 0x80);
}

t_bool	is_ldneg(long double ld)
{
	uint8_t	b;
	void	*p;

	p = &ld;
	b = *((uint8_t*)(p + 9));
	return ((b & 0x80) == 0x80);
}

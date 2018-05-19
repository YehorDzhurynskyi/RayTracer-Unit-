/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_frac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 12:30:36 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_float.h"

static unsigned	round(char *dest, unsigned precision)
{
	unsigned	i;

	if (precision == 0)
		return (dest[precision] > '5');
	else if (dest[precision] <= '5')
		return (0);
	dest[precision - 1]++;
	i = precision;
	while (i-- > 1)
	{
		if (dest[i] > '9')
		{
			dest[i] -= 10;
			dest[i - 1]++;
		}
	}
	if (dest[i] > '9')
	{
		dest[i] -= 10;
		return (1);
	}
	return (0);
}

unsigned		ft_get_ffrac(char *dest, unsigned precision, float f)
{
	float		frac;
	uint32_t	ufrac;
	unsigned	i;

	ufrac = (uint32_t)f;
	if (f < 0.0f)
	{
		f = -f;
		ufrac = ~ufrac + 1;
	}
	frac = f - ufrac;
	i = 0;
	while (i < precision + 1)
	{
		frac *= 10.0f;
		dest[i++] = ((uint32_t)frac) + '0';
		frac -= ((uint32_t)frac);
	}
	return (round(dest, precision));
}

unsigned		ft_get_dfrac(char *dest, unsigned precision, double d)
{
	double		frac;
	uint64_t	ufrac;
	unsigned	i;

	ufrac = (uint64_t)d;
	if (d < 0.0)
	{
		d = -d;
		ufrac = ~ufrac + 1;
	}
	frac = d - ufrac;
	i = 0;
	while (i < precision + 1)
	{
		frac *= 10.0;
		dest[i++] = ((uint64_t)frac) + '0';
		frac -= ((uint64_t)frac);
	}
	return (round(dest, precision));
}

unsigned		ft_get_ldfrac(char *dest, unsigned precision, long double ld)
{
	long double	frac;
	uint64_t	ufrac;
	unsigned	i;

	ufrac = (uint64_t)ld;
	if (ld < 0.0l)
	{
		ld = -ld;
		ufrac = ~ufrac + 1;
	}
	frac = ld - ufrac;
	i = 0;
	while (i < precision + 1)
	{
		frac *= 10.0l;
		dest[i++] = ((uint64_t)frac) + '0';
		frac -= ((uint64_t)frac);
	}
	return (round(dest, precision));
}

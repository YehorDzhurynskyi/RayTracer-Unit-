/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 16:11:48 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/24 18:03:57 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

static size_t		ft_count_digits(long long n)
{
	int l;

	if (n == 0)
		return (1);
	l = 0;
	while (n)
	{
		l++;
		n /= 10;
	}
	return (l);
}

static void			fill_buff(char *s, long long n, size_t count)
{
	if (n < 0)
		n = -n;
	while (count)
	{
		s[--count] = n % 10 + '0';
		n /= 10;
	}
}

static void			round_nearest(char *dest, unsigned precision)
{
	unsigned i;

	if (dest[precision - 1] <= '5')
		return ;
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
		dest[i] -= 10;
}

static void			fill_frac(char *dest, long double n, unsigned precision)
{
	int	i;

	if (n < 0.0)
		n = -n;
	i = 0;
	while (precision--)
	{
		n -= (long long)n;
		n *= 10.0;
		dest[i++] = (char)n + '0';
	}
}

char				*ft_ldtoa(long double n, unsigned precision)
{
	size_t		length;
	size_t		dec_length;
	char		*src;
	char		*s;

	dec_length = ft_count_digits((long long)n);
	length = dec_length + precision
	+ (precision > 0 ? 1 : 0) + (n < 0 ? 1 : 0);
	s = (char *)malloc(sizeof(char) * (length + 1));
	if (!s)
		return (NULL);
	s[length] = '\0';
	src = s;
	if (n < 0.0L)
		*s++ = '-';
	fill_buff(s, (long long)n, dec_length);
	if (precision > 0)
	{
		*(s + dec_length) = '.';
		fill_frac(s + dec_length + 1, n, precision);
		round_nearest(s + dec_length + 1, precision);
	}
	return (src);
}

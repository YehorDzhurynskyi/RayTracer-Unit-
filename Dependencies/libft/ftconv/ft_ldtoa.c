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

static long long	get_fractional_part(long double n, unsigned precision)
{
	int			p;
	long double	f;

	f = n - (long long)n;
	p = ft_powi(10, precision);
	return ((long long)((float)(f * p)));
}

char				*ft_ldtoa(long double n, unsigned precision)
{
	size_t		length;
	size_t		dec_length;
	char		*src;
	char		*s;
	long long	rpart;

	dec_length = ft_count_digits((long long)n);
	length = dec_length + precision
	+ (precision > 0 ? 1 : 0) + (n < 0 ? 1 : 0);
	s = (char *)malloc(sizeof(char) * (length + 1));
	if (!s)
		return (NULL);
	s[length] = '\0';
	src = s;
	if (n < 0)
		*s++ = '-';
	fill_buff(s, (long long)n, dec_length);
	if (precision > 0)
	{
		*(s + dec_length) = '.';
		rpart = get_fractional_part(n, precision);
		fill_buff(s + dec_length + 1, rpart, ft_count_digits(rpart));
	}
	return (src);
}

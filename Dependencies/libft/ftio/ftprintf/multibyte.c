/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibyte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multibyte.h"
#include "libft.h"

static unsigned int	count_bit(unsigned long long n)
{
	unsigned int	l;

	l = 0;
	while (n)
	{
		l++;
		n /= 2;
	}
	return (l);
}

static void			fill_bytes(wchar_t ch, char *dst, unsigned int size)
{
	unsigned int	i;

	i = size;
	dst[0] = (ch >> (size - 1) * 0x6) & ((0x80 >> size) - 1);
	while (i)
	{
		dst[0] |= 0x80 >> --i;
		if (i == 0)
			break ;
		dst[i] = ((ch >> (0x6 * (size - i - 1))) & 0x3F) | 0x80;
	}
}

unsigned int		to_multibyte(wchar_t ch, char *dst)
{
	unsigned int	size;
	unsigned int	bit_count;

	bit_count = count_bit(ch);
	if (bit_count <= 0x7)
		size = 1;
	else if (bit_count <= 0xB)
		size = 2;
	else if (bit_count <= 0x10)
		size = 3;
	else if (bit_count <= 0x15)
		size = 4;
	else
		return (0);
	if (size == 1)
	{
		dst[0] = ch;
		return (1);
	}
	fill_bytes(ch, dst, size);
	return (size);
}

char				*to_multibyte_str(const wchar_t *src, ssize_t wlen)
{
	char			*mbsrc;
	unsigned int	shift;

	mbsrc = ft_strnew(sizeof(char) * (wlen + 1));
	shift = 0;
	while (*src && shift < wlen)
		shift += to_multibyte(*src++, mbsrc + shift);
	return (mbsrc);
}

ssize_t				wstrlen(const wchar_t *src, t_conversion *c)
{
	ssize_t			size;
	unsigned int	bit_count;
	ssize_t			gain;

	size = 0;
	while (*src)
	{
		bit_count = count_bit(*src++);
		if (bit_count <= 0x7)
			gain = 1;
		else if (bit_count <= 0xB)
			gain = 2;
		else if (bit_count <= 0x10)
			gain = 3;
		else if (bit_count <= 0x15)
			gain = 4;
		else
			return (-1);
		if (c->precision != -1 && size + gain > c->precision)
			return (size);
		size += gain;
	}
	return (size);
}

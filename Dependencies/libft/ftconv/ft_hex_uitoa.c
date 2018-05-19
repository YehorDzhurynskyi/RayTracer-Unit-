/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_uitoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:10:51 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/27 13:57:05 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		g_upper_alphabet[] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
static char		g_lower_alphabet[] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static size_t	count_length(unsigned int n)
{
	size_t	l;

	if (n == 0)
		return (1);
	l = 0;
	while (n)
	{
		l++;
		n /= 16;
	}
	return (l);
}

char			*ft_hex_uitoa(unsigned int n,
		t_bool append_prefix, t_bool uppercase)
{
	size_t			l;
	char			*s;
	unsigned int	offset;

	l = append_prefix ? 2 : 0;
	l += count_length(n);
	s = ft_strnew(l);
	if (!s)
		return (NULL);
	offset = 0;
	if (append_prefix)
	{
		s[0] = '0';
		s[1] = uppercase ? 'X' : 'x';
		offset = 2;
	}
	while (l > offset)
	{
		if (uppercase)
			s[--l] = g_upper_alphabet[n % 16];
		else
			s[--l] = g_lower_alphabet[n % 16];
		n /= 16;
	}
	return (s);
}

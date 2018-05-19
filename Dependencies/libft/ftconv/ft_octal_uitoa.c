/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal_uitoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:10:51 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/27 13:57:05 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_length(unsigned int n)
{
	size_t	l;

	if (n == 0)
		return (1);
	l = 0;
	while (n)
	{
		l++;
		n /= 8;
	}
	return (l);
}

char			*ft_octal_uitoa(unsigned int n, t_bool append_prefix)
{
	size_t			l;
	char			*s;
	unsigned int	offset;

	l = append_prefix ? 1 : 0;
	l += count_length(n);
	s = ft_strnew(l);
	if (!s)
		return (NULL);
	offset = 0;
	if (append_prefix)
	{
		s[0] = '0';
		offset = 1;
	}
	while (l > offset)
	{
		s[--l] = n % 8 + '0';
		n /= 8;
	}
	return (s);
}

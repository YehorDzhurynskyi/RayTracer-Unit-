/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
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
		n /= 10;
	}
	return (l);
}

char			*ft_uitoa(unsigned int n)
{
	size_t			l;
	char			*s;

	l = count_length(n);
	s = ft_strnew(l);
	if (!s)
		return (NULL);
	while (l > 0)
	{
		s[--l] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}

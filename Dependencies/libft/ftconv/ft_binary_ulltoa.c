/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_ulltoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 13:02:02 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/29 13:17:54 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_length(unsigned long long n)
{
	size_t	l;

	if (n == 0)
		return (1);
	l = 0;
	while (n)
	{
		l++;
		n /= 2;
	}
	return (l);
}

char			*ft_binary_ulltoa(unsigned long long n)
{
	size_t			l;
	char			*s;

	l = count_length(n);
	s = ft_strnew(l);
	if (!s)
		return (NULL);
	while (l > 0)
	{
		s[--l] = n % 2 + '0';
		n /= 2;
	}
	return (s);
}

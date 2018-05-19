/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:39:56 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/28 13:23:09 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count_digits(long long n)
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

char		*ft_lltoa(long long n)
{
	int					l;
	unsigned long long	un;
	char				*str;

	l = n < 0 ? 1 : 0;
	if (n < 0)
		un = (unsigned long long)(~n + 1);
	else
		un = (unsigned long long)n;
	l += ft_count_digits(un);
	str = (char *)malloc(l + 1);
	if (!str)
		return (NULL);
	str[l] = '\0';
	while (l)
	{
		str[--l] = un % 10 + '0';
		un /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:39:56 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 15:37:28 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static int	ft_count_digits(unsigned int n)
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

char		*ft_itoa(int n)
{
	int				l;
	unsigned int	un;
	char			*str;

	l = n < 0 ? 1 : 0;
	if (n < 0)
		un = (unsigned int)(~n + 1);
	else
		un = (unsigned int)n;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:39:56 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 15:37:28 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static size_t	ft_count_digits(unsigned int n)
{
	size_t l;

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

void			ft_itoa_cat(char *dest, size_t size, int n)
{
	size_t			l;
	unsigned int	un;

	l = n < 0 ? 1 : 0;
	if (n < 0)
		un = (unsigned int)(~n + 1);
	else
		un = (unsigned int)n;
	l += ft_count_digits(un);
	if (l > size)
		return ;
	dest[l] = '\0';
	while (l)
	{
		dest[--l] = un % 10 + '0';
		un /= 10;
	}
	if (n < 0)
		dest[0] = '-';
}

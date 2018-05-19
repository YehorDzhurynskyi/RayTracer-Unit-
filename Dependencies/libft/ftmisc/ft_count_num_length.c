/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_num_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 14:16:14 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/27 14:17:25 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_num_length(unsigned long long n, unsigned base)
{
	size_t	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		l++;
		n /= base;
	}
	return (l);
}

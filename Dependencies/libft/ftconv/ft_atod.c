/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:27:27 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 13:07:42 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *s)
{
	double	n;
	double	f;
	double	d;
	int		sign;

	n = (double)ft_atoi(s);
	sign = 1;
	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	if (*s == '-')
		sign = -1;
	s = ft_strchr(s, '.');
	if (s == NULL)
		return (n);
	++s;
	f = 0.0;
	d = 10.0;
	while (*s >= '0' && *s <= '9')
	{
		f += (*s++ - '0') / d;
		d *= 10.0;
	}
	return (n + (f * sign));
}

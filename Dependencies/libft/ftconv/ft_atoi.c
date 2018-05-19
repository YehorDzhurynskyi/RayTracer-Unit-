/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:27:27 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 13:07:42 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int		my_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *u1;
	unsigned char *u2;

	u1 = (unsigned char *)s1;
	u2 = (unsigned char *)s2;
	while (*u1 && n)
	{
		if (*u1 != *u2)
			return (*u1 - *u2);
		u1++;
		u2++;
		n--;
	}
	if (*u2 && n)
		return (*u1 - *u2);
	return (0);
}

static int		ft_check_overflow(const char *s, int sign)
{
	char	*src_s;
	size_t	l;

	src_s = (char *)s;
	while (*s >= '0' && *s <= '9')
		s++;
	l = s - src_s;
	if (l == 19 && sign == -1
			&& my_strncmp("9223372036854775807", src_s, 19) < 0)
		return (0);
	else if (l == 19 && sign == 1 &&
			my_strncmp("9223372036854775807", src_s, 19) < 0)
		return (-1);
	if (l > 19 && sign == -1)
		return (0);
	else if (l > 19 && sign == 1)
		return (-1);
	return (1);
}

int				ft_atoi(const char *s)
{
	int	nb;
	int	sign;
	int	overflow;

	sign = 1;
	nb = 0;
	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	overflow = ft_check_overflow(s, sign);
	if (overflow != 1)
		return (overflow);
	while (*s >= '0' && *s <= '9')
		nb = nb * 10 + *s++ - '0';
	return (nb * sign);
}

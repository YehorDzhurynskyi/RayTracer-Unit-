/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:50:26 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:36:02 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned char *u1;
	unsigned char *u2;

	if (!s1 || !s2)
		return (0);
	u1 = (unsigned char *)s1;
	u2 = (unsigned char *)s2;
	while (*u1 && n)
	{
		if (*u1++ != *u2++)
			return (0);
		n--;
	}
	if (*u2 && n)
		return (0);
	return (1);
}

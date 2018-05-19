/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:01:18 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/26 14:25:31 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*u;
	unsigned char	ch;

	ch = (unsigned char)c;
	u = (unsigned char *)s;
	while (n--)
	{
		if (*u == ch)
			return (u);
		u++;
	}
	return (NULL);
}

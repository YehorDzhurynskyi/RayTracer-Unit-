/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:46:41 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:54:54 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrn(const char *s, int c, int n)
{
	char	*end;

	if (n == 0)
		return ((char *)s);
	if (n > 0)
	{
		while (*s)
		{
			if (c == *s && --n == 0)
				return ((char *)s);
			s++;
		}
	}
	else
	{
		end = ft_strrchr(s, '\0');
		while (end >= s)
		{
			if (c == *end && ++n == 0)
				return (end);
			end--;
		}
	}
	return (NULL);
}

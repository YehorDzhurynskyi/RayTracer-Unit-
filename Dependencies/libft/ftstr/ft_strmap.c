/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:39:04 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:30:29 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(const char *s)
{
	int l;

	l = 0;
	while (*s++)
		l++;
	return (l);
}

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*arr;
	char	*src;
	int		l;

	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	arr = (char *)malloc(l + 1);
	if (!arr)
		return (NULL);
	src = arr;
	arr[l] = '\0';
	while (*s)
		*arr++ = f(*s++);
	return (src);
}

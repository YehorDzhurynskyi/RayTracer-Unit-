/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:45:15 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:42:54 by ydzhuryn         ###   ########.fr       */
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

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*arr;
	char			*src;
	int				l;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	arr = (char *)malloc(l + 1);
	if (!arr)
		return (NULL);
	src = arr;
	arr[l] = '\0';
	i = 0;
	while (*s)
		*arr++ = f(i++, *s++);
	return (src);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:43:41 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:32:44 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static	size_t	ft_strlen(const char *s1)
{
	size_t l;

	l = 0;
	while (*s1++)
		l++;
	return (l);
}

char			*ft_strdup(const char *s1)
{
	char	*res;
	int		l;

	l = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (l + 1));
	if (!res)
		return (NULL);
	res[l] = '\0';
	while (l--)
		res[l] = s1[l];
	return (res);
}

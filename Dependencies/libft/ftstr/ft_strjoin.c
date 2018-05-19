/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:00:37 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/14 16:19:34 by ydzhuryn         ###   ########.fr       */
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

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*con;
	int		l;
	char	*src;

	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2);
	con = (char *)malloc(l + 1);
	if (!con)
		return (NULL);
	src = con;
	con[l] = '\0';
	while (*s1)
		*con++ = *s1++;
	while (*s2)
		*con++ = *s2++;
	return (src);
}

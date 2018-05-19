/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:58:14 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/26 14:53:31 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int		ft_equals(const char *s1, const char *s2)
{
	while (*s2)
		if (*s1++ != *s2++)
			return (0);
	return (1);
}

static size_t	ft_strlen(const char *s)
{
	size_t l;

	l = 0;
	while (*s++)
		l++;
	return (l);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*cbig;
	size_t	little_len;

	cbig = (char *)big;
	if (!*little)
		return (cbig);
	little_len = ft_strlen(little);
	while (*cbig && len)
	{
		if (len < little_len)
			return (NULL);
		if (ft_equals(cbig, little))
			return (cbig);
		cbig++;
		len--;
	}
	return (NULL);
}

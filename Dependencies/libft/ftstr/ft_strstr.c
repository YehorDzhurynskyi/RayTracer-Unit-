/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:45:53 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:30:04 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_equals(const char *s1, const char *s2)
{
	while (*s2)
		if (*s1++ != *s2++)
			return (0);
	return (1);
}

char		*ft_strstr(const char *big, const char *little)
{
	char *cbig;

	cbig = (char *)big;
	if (!*little)
		return (cbig);
	while (*cbig)
	{
		if (ft_equals(cbig, little))
			return (cbig);
		cbig++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:36:35 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/25 20:15:41 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnchr(const char *ss, int c, int n)
{
	char *s;

	s = (char *)ss;
	while (*s && n)
	{
		if (*s == (char)c)
			return (s);
		s++;
		n--;
	}
	return (*s == (char)c && n ? s : NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:42:51 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 13:01:13 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *ss, int c)
{
	char *start;
	char *s;

	s = (char *)ss;
	start = s;
	while (*s)
		s++;
	if ((char)c == '\0')
		return (s);
	while (s >= start)
	{
		if (*s == (char)c)
			return (s);
		s--;
	}
	return (NULL);
}

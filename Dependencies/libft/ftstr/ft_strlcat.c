/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:21:04 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 19:27:45 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static size_t	ft_strlen(const char *s)
{
	size_t l;

	l = 0;
	while (*s++)
		l++;
	return (l);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*ddst;
	size_t	rest;
	size_t	dst_l;
	size_t	src_l;

	ddst = dst;
	rest = size;
	while (*ddst && rest && rest--)
		ddst++;
	src_l = ft_strlen(src);
	dst_l = (size_t)(ddst - dst);
	rest = size - dst_l;
	if (!rest)
		return (dst_l + src_l);
	while (*src)
	{
		if (rest-- != 1)
			*ddst++ = *src++;
		else
			break ;
	}
	*ddst = '\0';
	return (dst_l + src_l);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_file_names.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:47:03 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/03 15:27:11 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file.h"
#include "libft.h"

static inline t_bool	ends_with(const char *s, char c)
{
	while (*s)
		s++;
	return (*(s - 1) == c);
}

char					*ft_merge_file_names(const char *s1, const char *s2)
{
	char	*merged;
	t_bool	ends_with_slash;
	t_bool	starts_with_slash;
	size_t	l1;
	size_t	l2;

	starts_with_slash = *s2 == '/';
	ends_with_slash = ends_with(s1, '/');
	l2 = ft_strlen(s2);
	l1 = ft_strlen(s1) + (starts_with_slash && ends_with_slash ? -1 : 0);
	merged = ft_strnew(l1 + l2
			+ (!ends_with_slash && !starts_with_slash ? 1 : 0));
	if (!merged)
		return (NULL);
	ft_memcpy(merged, s1, l1);
	if (!ends_with_slash && !starts_with_slash)
		ft_memset(merged + l1, '/', sizeof(char));
	ft_memcpy(merged + l1
			+ (!ends_with_slash && !starts_with_slash ? 1 : 0), s2, l2);
	return (merged);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplallstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:04:55 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/30 14:06:23 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static size_t	count_length(char const *s, char const *from, char const *to)
{
	size_t			from_len;
	size_t			len;
	unsigned int	from_count;
	unsigned int	i;

	from_count = 0;
	len = ft_strlen(s);
	from_len = ft_strlen(from);
	while (s)
	{
		s = ft_strstr(s, from);
		if (!s)
			break ;
		i = 0;
		while (i++ < from_len)
			s++;
		from_count++;
	}
	len += from_count * (ft_strlen(to) - from_len);
	return (len);
}

static void		write_str(char const **s, char const *from,
		char const *to, char **new)
{
	unsigned int	i;
	size_t			to_len;
	size_t			from_len;

	to_len = ft_strlen(to);
	from_len = ft_strlen(from);
	ft_memcpy(*new, to, to_len);
	i = 0;
	while (i++ < from_len)
		(*s)++;
	i = 0;
	while (i++ < to_len)
		(*new)++;
}

char			*ft_strreplallstr(char const *s, char const *from,
		char const *to)
{
	size_t	len;
	size_t	from_len;
	char	*new;
	char	*src;

	if (!s || !from || !to)
		return (NULL);
	from_len = ft_strlen(from);
	len = count_length(s, from, to);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	src = new;
	new[len] = '\0';
	while (*s)
	{
		if (ft_strnequ(s, from, from_len))
			write_str(&s, from, to, &new);
		else
			*new++ = *s++;
	}
	return (src);
}

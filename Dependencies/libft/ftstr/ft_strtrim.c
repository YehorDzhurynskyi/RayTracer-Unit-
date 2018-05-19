/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:05:14 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 13:36:59 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static int	ft_strlen(const char *s)
{
	int l;

	l = 0;
	while (*s++)
		l++;
	return (l);
}

static int	ft_strtrimlen(char *s, char **start, char **end)
{
	int l;

	*start = s;
	*end = s + ft_strlen(s) - 1;
	l = 0;
	while (**end == '\n' || **end == ' ' || **end == '\t')
		(*end)--;
	while (*s == '\n' || *s == ' ' || *s == '\t')
		s++;
	*start = s;
	while (s++ <= *end)
		l++;
	return (l);
}

char		*ft_strtrim(char const *s)
{
	char	*new;
	int		l;
	char	*end;
	char	*src;
	char	*cs;

	if (!s)
		return (NULL);
	cs = (char *)s;
	l = ft_strtrimlen(cs, &cs, &end);
	new = (char *)malloc(l + 1);
	if (!new)
		return (NULL);
	src = new;
	new[l] = '\0';
	while (cs <= end)
		*new++ = *cs++;
	*new = '\0';
	return (src);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:22:13 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 17:38:36 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static int	ft_count_words(char const *s, char c)
{
	int l;

	l = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			l++;
		while (*s != c && *s)
			s++;
		if (*s)
			s++;
	}
	return (l);
}

static char	*ft_compose_word(const char **s, char c)
{
	char	*new;
	size_t	l;
	char	*src;
	char	*ssrc;

	l = 0;
	while (**s == c)
		(*s)++;
	ssrc = (char *)*s;
	while (**s != c && **s)
	{
		l++;
		(*s)++;
	}
	new = (char *)malloc(sizeof(char) * (l + 1));
	if (!new)
		return (NULL);
	src = new;
	new[l] = '\0';
	while (*ssrc != c && *ssrc)
		*new++ = *ssrc++;
	return (src);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		cc;
	int		i;

	if (!s)
		return (NULL);
	cc = ft_count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (cc + 1));
	if (!tab)
		return (NULL);
	tab[cc] = NULL;
	i = 0;
	while (i < cc)
		tab[i++] = ft_compose_word(&s, c);
	return (tab);
}

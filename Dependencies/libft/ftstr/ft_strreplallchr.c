/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplallchr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:45:46 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/30 13:45:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strreplallchr(char const *s, char from, char to)
{
	char	*new;
	char	*src;
	size_t	len;

	if (!from || !to || !s)
		return (NULL);
	len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	src = new;
	new[len] = '\0';
	while (*s)
	{
		if (*s == from)
			*new = to;
		else
			*new = *s;
		s++;
		new++;
	}
	return (src);
}

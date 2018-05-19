/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:55:38 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/26 15:54:54 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*arr;

	if (!s)
		return (NULL);
	arr = (char *)malloc(len + 1);
	if (!arr)
		return (NULL);
	arr[len] = '\0';
	while (len--)
		arr[len] = s[len + start];
	return (arr);
}

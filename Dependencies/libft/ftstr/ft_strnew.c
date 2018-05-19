/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:26:34 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/19 15:27:32 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char	*arr;

	arr = (char *)malloc(size + 1);
	if (!arr)
		return (NULL);
	arr[size] = '\0';
	while (size)
		arr[--size] = '\0';
	return (arr);
}

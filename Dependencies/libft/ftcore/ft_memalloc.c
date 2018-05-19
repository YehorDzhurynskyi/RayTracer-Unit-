/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:19:33 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:34:07 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char *arr;

	arr = (char *)malloc(size);
	if (!arr)
		return (NULL);
	while (size--)
		arr[size] = '\0';
	return ((void *)arr);
}

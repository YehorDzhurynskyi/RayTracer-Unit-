/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alst_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:07:39 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:17:09 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alst.h"
#include <stdlib.h>

void		*alst_to_array(t_alst *alst, void (*collector)(void *arr, void
			*item, unsigned int offset), size_t size)
{
	void			*arr;
	unsigned int	i;

	arr = malloc(size * alst->size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < alst->size)
	{
		collector(arr, alst_get(alst, i), size * i);
		i++;
	}
	return (arr);
}

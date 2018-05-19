/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:53:42 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 16:18:18 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_amap.h"

void	*amap_get(const t_amap *map, int key)
{
	t_alst			*lst;
	t_amap_item		*item;
	unsigned int	i;

	lst = map->items[key % map->size];
	if (!lst)
		return (NULL);
	i = 0;
	while (i < lst->size)
	{
		item = (t_amap_item *)alst_get(lst, i);
		if (item->key == key)
			return (item->content);
		i++;
	}
	return (NULL);
}

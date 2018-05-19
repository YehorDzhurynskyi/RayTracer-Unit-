/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:53:42 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 16:18:18 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_amap.h"

void	amap_clear(t_amap *map, void (*clear)(void **item))
{
	t_alst			*lst;
	unsigned int	i;
	unsigned int	j;
	t_amap_item		*item;

	j = 0;
	while (j < map->size)
	{
		lst = map->items[j++];
		if (!lst)
			continue ;
		i = 0;
		while (i < lst->size)
		{
			item = (t_amap_item *)alst_get(lst, i);
			if (clear)
				clear((void**)&item->content);
			i++;
		}
		alst_clear(lst, ft_memdel);
		alst_del(&lst);
	}
	ft_memdel((void**)&map->items);
}

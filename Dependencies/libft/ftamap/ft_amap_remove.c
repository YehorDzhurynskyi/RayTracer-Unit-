/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:13:09 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/19 14:58:32 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_amap.h"

t_bool	amap_remove(t_amap *map, int key, void (*clear)(void **item))
{
	t_alst			*lst;
	unsigned int	i;
	t_bool			res;
	t_amap_item		*item;

	lst = map->items[key % map->size];
	if (!lst)
		return (FALSE);
	i = 0;
	res = FALSE;
	while (i < lst->size)
	{
		item = (t_amap_item *)alst_get(lst, i);
		if (item->key == key)
		{
			if (clear)
				clear((void**)&item->content);
			res = alst_remove(lst, ft_memdel, i);
		}
		i++;
	}
	if (lst->size == 0)
		alst_del(map->items + key % map->size);
	return (res);
}

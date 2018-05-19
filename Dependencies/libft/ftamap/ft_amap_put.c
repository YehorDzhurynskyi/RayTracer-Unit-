/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:36:02 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 16:18:28 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_amap.h"
#include <stdlib.h>

t_bool	amap_put(t_amap *map, int key, void *content)
{
	t_alst		*lst;
	t_amap_item	*item;

	if (amap_contains(map, key))
		return (FALSE);
	lst = map->items[key % map->size];
	if (!lst)
	{
		lst = alst_create(3);
		map->items[key % map->size] = lst;
	}
	if (!lst)
		return (FALSE);
	item = (t_amap_item *)malloc(sizeof(t_amap_item));
	if (!item)
		return (FALSE);
	item->key = key;
	item->content = content;
	alst_add(lst, item);
	return (TRUE);
}

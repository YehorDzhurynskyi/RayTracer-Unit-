/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap_contains.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:45:26 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:06:44 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_amap.h"

t_bool	amap_contains(const t_amap *map, int key)
{
	t_alst			*lst;
	unsigned int	i;
	t_amap_item		*item;

	lst = map->items[key % map->size];
	if (!lst)
		return (FALSE);
	i = 0;
	while (i < lst->size)
	{
		item = (t_amap_item *)alst_get(lst, i);
		if (item->key == key)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

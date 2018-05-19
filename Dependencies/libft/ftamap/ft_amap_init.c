/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:53:42 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 16:18:18 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_amap.h"
#include <stdlib.h>

t_bool	amap_init(t_amap *map, size_t capacity)
{
	if (!map)
		return (FALSE);
	map->items = (t_alst **)malloc(sizeof(t_alst *) * capacity);
	if (!map->items)
		return (FALSE);
	ft_memset(map->items, 0, sizeof(t_alst *) * capacity);
	map->size = capacity;
	return (TRUE);
}

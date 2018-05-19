/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:29:58 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:05:30 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_amap.h"
#include <stdlib.h>

t_amap	*amap_create(size_t capacity)
{
	t_amap	*map;

	map = (t_amap *)malloc(sizeof(t_amap));
	if (!map)
		return (NULL);
	if (!amap_init(map, capacity))
		ft_memdel((void**)&map);
	return (map);
}

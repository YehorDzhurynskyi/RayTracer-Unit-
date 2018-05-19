/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:24:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/16 13:12:59 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AMAP_H
# define FT_AMAP_H

# include "ft_alst.h"
# include "libft.h"

typedef struct
{
	t_alst	**items;
	size_t	size;
}	t_amap;

typedef struct
{
	int		key;
	void	*content;
}			t_amap_item;

t_amap		*amap_create(size_t capacity);
t_bool		amap_init(t_amap *map, size_t capacity);
t_bool		amap_contains(const t_amap *map, int key);
t_bool		amap_put(t_amap *map, int key, void *content);
void		*amap_get(const t_amap *map, int key);
t_bool		amap_remove(t_amap *map, int key, void (*clear)(void **item));
void		amap_clear(t_amap *map, void (*clear)(void **item));

#endif

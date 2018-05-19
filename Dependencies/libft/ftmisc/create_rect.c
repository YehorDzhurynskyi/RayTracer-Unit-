/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:23:35 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/27 15:26:44 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rect.h"
#include <stdlib.h>

t_rect	*create_rect(unsigned int x, unsigned int y, size_t w, size_t h)
{
	t_rect	*rect;

	rect = (t_rect *)malloc(sizeof(t_rect));
	if (!rect)
		return (NULL);
	rect->x = x;
	rect->y = y;
	rect->width = w;
	rect->height = h;
	return (rect);
}

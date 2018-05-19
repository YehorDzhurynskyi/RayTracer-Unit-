/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:21:55 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/27 15:27:18 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECT_H
# define RECT_H

# include "libft.h"

typedef struct
{
	unsigned int	x;
	unsigned int	y;
	size_t			width;
	size_t			height;
}					t_rect;

t_rect				*create_rect(unsigned int x, unsigned int y,
		size_t w, size_t h);

#endif

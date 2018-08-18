/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_shape	scenebuffer_default_shape(void)
{
	t_shape	shape;

	shape.relation_type = UNION;
	shape.nchildren = 0;
	shape.material_addr = DEFAULT_MATERIAL_ID;
	return (shape);
}

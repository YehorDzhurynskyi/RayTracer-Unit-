/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_limitation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneiterator.h"

t_iterator			limitation_begin(const t_primitive *primitive)
{
	return ((t_iterator){primitive->nlimitations, primitive_skip(primitive)});
}

const t_limitation	*limitation_next(t_iterator *iterator)
{
	const t_limitation	*current;

	current = (const t_limitation*)iterator->current;
	iterator->current = limitation_skip(current);
	--iterator->count;
	return (current);
}

const t_byte		*limitation_get_actual(const t_limitation *limitation)
{
	return ((const t_byte*)++limitation);
}

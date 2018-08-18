/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_limitation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include <assert.h>

static size_t	limitation_size(t_limitation_type type)
{
	if (IS_AXIAL(type))
		return (sizeof(t_axial_limitation));
	assert(FALSE && "Shape structure instance should have shapetype field");
	return (0);
}

void			scenebuffer_add_limitation(t_scene *scene, const t_limitation
*limitation, const void *actual_limitation, t_buff_target target)
{
	scenebuffer_append(scene, limitation,
	sizeof(t_limitation), target);
	scenebuffer_append(scene, actual_limitation,
	limitation_size(limitation->limitation_type), target);
}

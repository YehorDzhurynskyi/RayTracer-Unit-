/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_primitive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_primitive	scenebuffer_default_primitive(void)
{
	t_primitive	primitive;
	t_vec3d		position;

	primitive.orientation = to_orientation_matrix(0.0f, 0.0f, 0.0f);
	position = scenebuffer_default_position();
	primitive.position.x = position.x;
	primitive.position.y = position.y;
	primitive.position.z = position.z;
	primitive.nlimitations = 0;
	return (primitive);
}

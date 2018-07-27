/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneiterator.h"

t_bool			has_next(const t_iterator *iterator)
{
	return (iterator->count > 0);
}

const t_byte	*primitive_get_actual(const t_primitive *primitive)
{
	return ((const t_byte*)++primitive);
}

const t_byte	*primitive_skip(const t_primitive *primitive)
{
	const t_byte	*ptr = (const t_byte*)primitive;
	ptr += sizeof(t_primitive);
	if (primitive->primitive_type == SPHERE)
		ptr += sizeof(t_sphere);
	else if (primitive->primitive_type == CONE)
		ptr += sizeof(t_cone);
	else if (primitive->primitive_type == CYLINDER)
		ptr += sizeof(t_cylinder);
	return (ptr);
}

const t_byte	*lightsource_skip(const t_lightsource *lightsource)
{
	const t_byte	*lightsource_ptr = (const t_byte*)lightsource;
	lightsource_ptr += sizeof(t_lightsource);
	if (lightsource->lightsource_type == DIRLIGHT)
		lightsource_ptr += sizeof(t_dirlightsource);
	else if (lightsource->lightsource_type == POINTLIGHT)
		lightsource_ptr += sizeof(t_pointlightsource);
	else if (lightsource->lightsource_type == SPOTLIGHT)
		lightsource_ptr += sizeof(t_spotlightsource);
	return (lightsource_ptr);
}

const t_byte	*limitation_skip(const t_limitation *limitation)
{
	const t_byte	*ptr = (const t_byte*)limitation;
	ptr += sizeof(t_limitation);
	if (IS_AXIAL(limitation->limitation_type))
		ptr += sizeof(t_axial_limitation);
	return (ptr);
}
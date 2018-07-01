/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sceneiterator.cl                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneiterator.h"

static const t_byte	*limitation_skip(const t_limitation *limitation)
{
	const t_byte	*limitation_ptr = (const t_byte*)limitation;
	limitation_ptr += sizeof(t_limitation);
	if (IS_AXIAL(limitation->limitation_type))
		limitation_ptr += sizeof(t_axial_limitation);
	return (limitation_ptr);
}

static const t_byte	*primitive_skip(const t_primitive *primitive)
{
	const t_byte	*primitive_ptr = (const t_byte*)primitive;
	primitive_ptr += sizeof(t_primitive);
	if (primitive->primitive_type == SPHERE)
		primitive_ptr += sizeof(t_sphere);
	else if (primitive->primitive_type == CONE)
		primitive_ptr += sizeof(t_cone);
	else if (primitive->primitive_type == CYLINDER)
		primitive_ptr += sizeof(t_cylinder);
	return (primitive_ptr);
}

static const t_byte	*lightsource_skip(const t_lightsource *lightsource)
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

t_iterator					shape_begin(const t_scene *scene)
{
	return ((t_iterator){scene->meta.nshapes, scene->host_shapebuffer});
}

t_iterator					lightsource_begin(const t_scene *scene)
{
	return ((t_iterator){scene->meta.nlightsources, scene->host_lightsourcebuffer});
}

t_iterator					material_begin(const t_scene *scene)
{
	return ((t_iterator){scene->meta.nmaterials, scene->host_materialbuffer});
}

t_iterator					limitation_begin(const t_primitive *primitive)
{
	const t_byte	*limitation_ptr = primitive_skip(primitive);
	return ((t_iterator){primitive->nlimitations, limitation_ptr});
}

const t_shape			*shape_next(t_iterator *iterator)
{
	const t_shape	*current = (const t_shape*)iterator->current;
	int nchildren = current->nchildren;
	while (nchildren-- >= 0)
	{
		iterator->current += sizeof(t_shape);
		iterator->current = primitive_skip((const t_primitive*)iterator->current);
		const t_shape	*child = (const t_shape*)iterator->current;
		nchildren += child->nchildren;
	}
	--iterator->count;
	return (current);
}

const t_lightsource	*lightsource_next(t_iterator *iterator)
{
	const t_lightsource	*current = (const t_lightsource*)iterator->current;
	iterator->current = lightsource_skip(current);
	t_iterator limitation_iter = limitation_begin((const t_primitive*)iterator->current);
	while (has_next(&limitation_iter))
		limitation_next(&limitation_iter);
	iterator->current = limitation_iter.current;
	--iterator->count;
	return (current);
}

const t_material		*material_next(t_iterator *iterator)
{
	const t_material	*current = (const t_material*)iterator->current;
	iterator->current += sizeof(t_material);
	--iterator->count;
	return (current);
}

const t_limitation		*limitation_next(t_iterator *iterator)
{
	const t_limitation	*current = (const t_limitation*)iterator->current;
	iterator->current = limitation_skip(current);
	--iterator->count;
	return (current);
}

t_bool						has_next(const t_iterator *iterator)
{
	return (iterator->count > 0);
}

const t_primitive		*shape_get_primitive(const t_shape *shape)
{
	return ((const t_primitive*)++shape);
}

const t_primitive		*lightsource_get_primitive(const t_lightsource *lightsource)
{
	return ((const t_primitive*)lightsource_skip(lightsource));
}

const t_byte			*primitive_get_actual(const t_primitive *primitive)
{
	return((const t_byte*)++primitive);
}

const t_byte			*lightsource_get_actual(const t_lightsource *lightsource)
{
	return ((const t_byte*)++lightsource);
}

const t_byte			*limitation_get_actual(const t_limitation *limitation)
{
	return((const t_byte*)++limitation);
}

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

static __constant t_byte	*limitation_skip(__constant t_limitation *limitation)
{
	__constant t_byte	*ptr = (__constant t_byte*)limitation;
	ptr += sizeof(t_limitation);
	if (IS_AXIAL(limitation->limitation_type))
		ptr += sizeof(t_axial_limitation);
	return (ptr);
}

static __constant t_byte	*lightsource_skip(__constant t_lightsource *lightsource)
{
	__constant t_byte	*lightsource_ptr = (__constant t_byte*)lightsource;
	lightsource_ptr += sizeof(t_lightsource);
	if (lightsource->lightsource_type == DIRLIGHT)
		lightsource_ptr += sizeof(t_dirlightsource);
	else if (lightsource->lightsource_type == POINTLIGHT)
		lightsource_ptr += sizeof(t_pointlightsource);
	else if (lightsource->lightsource_type == SPOTLIGHT)
		lightsource_ptr += sizeof(t_spotlightsource);
	return (lightsource_ptr);
}

static __constant t_byte	*primitive_skip(__constant t_primitive *primitive)
{
	__constant t_byte	*ptr = (__constant t_byte*)primitive;
	ptr += sizeof(t_primitive);
	if (primitive->primitive_type == SPHERE)
		ptr += sizeof(t_sphere);
	else if (primitive->primitive_type == CONE)
		ptr += sizeof(t_cone);
	else if (primitive->primitive_type == CYLINDER)
		ptr += sizeof(t_cylinder);
	return (ptr);
}

t_iterator			shape_begin(const t_scene *scene, const t_scene_buffers *buffers)
{
	return ((t_iterator){scene->meta.nshapes, buffers->shapebuffer});
}

__constant t_shape	*shape_next(t_iterator *iterator)
{
	__constant t_shape	*current = (__constant t_shape*)iterator->current;
	int nchildren = current->nchildren;
	while (nchildren-- >= 0)
	{
		iterator->current += sizeof(t_shape);
		t_iterator limitation_iter = limitation_begin((__constant t_primitive*)iterator->current);
		while (has_next(&limitation_iter))
			limitation_next(&limitation_iter);
		iterator->current = limitation_iter.current;
		if (nchildren >= 0)
		{
			__constant t_shape	*child = (__constant t_shape*)iterator->current;
			nchildren += child->nchildren;
		}
	}
	--iterator->count;
	return (current);
}

t_iterator			lightsource_begin(const t_scene *scene, const t_scene_buffers *buffers)
{
	return ((t_iterator){scene->meta.nlightsources, buffers->lightsourcebuffer});
}

__constant t_lightsource	*lightsource_next(t_iterator *iterator)
{
	__constant t_lightsource	*current = (__constant t_lightsource*)iterator->current;
	iterator->current = lightsource_skip(current);
	if (current->lightsource_type == POINTLIGHT || current->lightsource_type == SPOTLIGHT)
	{
		t_iterator limitation_iter = limitation_begin((__constant t_primitive*)iterator->current);
		while (has_next(&limitation_iter))
			limitation_next(&limitation_iter);
		iterator->current = limitation_iter.current;
	}
	--iterator->count;
	return (current);
}

t_iterator					limitation_begin(__constant t_primitive *primitive)
{
	return ((t_iterator){primitive->nlimitations, primitive_skip(primitive)});
}

__constant t_limitation		*limitation_next(t_iterator *iterator)
{
	__constant t_limitation	*current = (__constant t_limitation*)iterator->current;
	iterator->current = limitation_skip(current);
	--iterator->count;
	return (current);
}

t_bool				has_next(const t_iterator *iterator)
{
	return (iterator->count > 0);
}

__constant t_primitive	*shape_get_primitive(__constant t_shape *shape)
{
	return ((__constant t_primitive*)++shape);
}

__constant t_byte	*primitive_get_actual(__constant t_primitive *primitive)
{
	return ((__constant t_byte*)++primitive);
}

__constant t_byte			*lightsource_get_actual(__constant t_lightsource *lightsource)
{
	return ((__constant t_byte*)++lightsource);
}

__constant t_byte			*limitation_get_actual(__constant t_limitation *limitation)
{
	return ((__constant t_byte*)++limitation);
}


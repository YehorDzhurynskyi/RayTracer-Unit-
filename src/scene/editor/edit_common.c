/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include <assert.h>
#include "logger.h"

static void		determine_target_buffer_size(t_scene *scene,
size_t *buffer_size, size_t *buffer_capacity, t_buff_target target)
{
	if (target == SHAPEBUFF_TARGET)
	{
		*buffer_size = scene->meta.shapes_size;
		*buffer_capacity = SHAPEBUFF_CAPACITY;
	}
	else if (target == LIGHTSOURCEBUFF_TARGET)
	{
		*buffer_size = scene->meta.lightsources_size;
		*buffer_capacity = LIGHTSOURCEBUFF_CAPACITY;
	}
	else if (target == MATERIALBUFF_TARGET)
	{
		*buffer_size = scene->meta.materials_size;
		*buffer_capacity = MATERIALBUFF_CAPACITY;
	}
	else if (target == TEXTUREBUFF_TARGET)
	{
		*buffer_size = scene->meta.textures_size;
		*buffer_capacity = TEXTUREBUFF_CAPACITY;
	}
	else
	{
		assert("Unrecognized target" == NULL);
	}
}

void			scenebuffer_put(t_scene *scene, const void *data,
int offset, size_t size)
{
	assert(scene->mapped_device_buffer != NULL);
	assert(scene->mapped_host_buffer != NULL);
	ft_memcpy(scene->mapped_device_buffer + offset, data, size);
	ft_memcpy(scene->mapped_host_buffer + offset, data, size);
}

void			scenebuffer_append(t_scene *scene, const void *data,
size_t size, t_buff_target target)
{
	size_t	buffer_size;
	size_t	buffer_capacity;

	determine_target_buffer_size(scene, &buffer_size, &buffer_capacity, target);
	if (buffer_size + size > buffer_capacity)
	{
		log_error("Reached the maximum number of instances in scene",
		RT_BUFFER_OVERFLOW_ERROR);
		return ;
	}
	if (target == SHAPEBUFF_TARGET)
		scene->meta.shapes_size += size;
	else if (target == LIGHTSOURCEBUFF_TARGET)
		scene->meta.lightsources_size += size;
	else if (target == MATERIALBUFF_TARGET)
		scene->meta.materials_size += size;
	else if (target == TEXTUREBUFF_TARGET)
		scene->meta.textures_size += size;
	scenebuffer_put(scene, data, 0, size);
	scene->mapped_device_buffer += size;
	scene->mapped_host_buffer += size;
}

static size_t	primitive_size(t_primitive_type type)
{
	if (type == PLANE)
		return (0);
	else if (type == SPHERE)
		return (sizeof(t_sphere));
	else if (type == CONE)
		return (sizeof(t_cone));
	else if (type == CYLINDER)
		return (sizeof(t_cylinder));
	else if (type == TORUS)
		return (sizeof(t_torus));
	else if (type == QUADRIC)
		return (sizeof(t_quadric_surface));
	else if (type == PARALLELEPIPED)
		return (sizeof(t_parallelepiped));
	assert(FALSE && "Primitive structure instance should"
	" have primitivetype field");
	return (0);
}

void			scenebuffer_add_primitive(t_scene *scene,
const t_primitive *primitive, const void *actual_primitive, t_buff_target trgt)
{
	scenebuffer_append(scene, primitive,
	sizeof(t_primitive), trgt);
	if (actual_primitive != NULL)
		scenebuffer_append(scene, actual_primitive,
		primitive_size(primitive->primitive_type), trgt);
}

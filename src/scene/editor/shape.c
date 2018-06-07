/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include "error.h"
#include <assert.h>

void			scene_add_shape(t_scene *scene, t_shape *shape,
const void *actual_shape)
{
	void	*dest;
	size_t	sizeof_actualshape;

	sizeof_actualshape = shape_sizeof(shape->shapetype);
	if (scene->shapebuffer_size + sizeof(t_shape) + sizeof_actualshape > SHAPEBUFFER_CAPACITY)
		print_error("Reached the maximum number of shapes in scene"); // TODO: don't exit the program just print message and return
	shape->buffer_offset = scene->shapebuffer_size;
	scene->nshapes++;
	dest = scene->host_shapebuffer + scene->shapebuffer_size;
	ft_memcpy(dest, shape, sizeof(t_shape));
	ft_memcpy(dest + sizeof(t_shape), actual_shape, sizeof_actualshape);
	scene->shapebuffer_size += sizeof(t_shape) + sizeof_actualshape;
}

void			scene_update_shape(t_scene *scene,
const t_shape *shape, const void *actual_shape)
{
	void	*dest;
	size_t	sizeof_actualshape;

	sizeof_actualshape = shape_sizeof(shape->shapetype);
	dest = scene->host_shapebuffer + shape->buffer_offset;
	ft_memcpy(dest, shape, sizeof(t_shape));
	ft_memcpy(dest + sizeof(t_shape), actual_shape, sizeof_actualshape);
}

static void		update_shape_buffer_offsets(void *shapebuffer,
unsigned int offset, size_t size_to_update)
{
	t_shape			*shape;
	unsigned int	step;
	unsigned int	init_offset;

	init_offset = offset;
	while (size_to_update > 0)
	{
		shape = (t_shape*)(shapebuffer + (offset - init_offset));
		shape->buffer_offset = offset;
		step = sizeof(t_shape) + shape_sizeof(shape->shapetype);
		size_to_update -= step;
		offset += step;
	}
}

inline size_t	shape_sizeof(t_shape_type type)
{
	if (type == PLANE)
		return (sizeof(t_plane));
	else if (type == SPHERE)
		return (sizeof(t_sphere));
	else if (type == CONE)
		return (sizeof(t_cone));
	else if (type == CYLINDER)
		return (sizeof(t_cylinder));
	assert(FALSE && "Shape structure instance should have shapetype field");
	return (0);
}

void			scene_remove_shape(t_scene *scene,
const t_shape *shape)
{
	void	*dest;
	void	*after_shape_ptr;
	size_t	after_shape_size;
	size_t	sizeof_actualshape;

	sizeof_actualshape = shape_sizeof(shape->shapetype);
	dest = scene->host_shapebuffer + shape->buffer_offset;
	after_shape_ptr = dest + sizeof(t_shape) + sizeof_actualshape;
	after_shape_size = scene->shapebuffer_size
	- (after_shape_ptr - scene->host_shapebuffer);
	ft_memcpy(dest, after_shape_ptr, after_shape_size);
	update_shape_buffer_offsets(dest, dest - scene->host_shapebuffer,
	after_shape_size);
	scene->shapebuffer_size -= sizeof(t_shape) + sizeof_actualshape;
	scene->nshapes--;
}

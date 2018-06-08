/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include "logger.h"
#include <assert.h>

// TODO: the code of this and sceneeditor_shape.c file are pretty the same
// so need to take logic into a separate file

void			scene_add_light(t_scene *scene, t_light *light,
const void *actual_light)
{
	void	*dest;
	size_t	sizeof_actuallight;

	sizeof_actuallight = light_sizeof(light->lighttype);
	if (scene->lightbuffer_size + sizeof(t_light) + sizeof_actuallight > LIGHTBUFFER_CAPACITY)
		log_error("Reached the maximum number of lights in scene", RT_BUFFER_OVERFLOW_ERROR);
	light->buffer_offset = scene->lightbuffer_size;
	scene->nlights++;
	dest = scene->host_lightbuffer + scene->lightbuffer_size;
	ft_memcpy(dest, light, sizeof(t_light));
	ft_memcpy(dest + sizeof(t_light), actual_light, sizeof_actuallight);
	scene->lightbuffer_size += sizeof(t_light) + sizeof_actuallight;
}

void			scene_update_light(t_scene *scene,
const t_light *light, const void *actual_light)
{
	void	*dest;
	size_t	sizeof_actuallight;

	sizeof_actuallight = light_sizeof(light->lighttype);
	dest = scene->host_lightbuffer + light->buffer_offset;
	ft_memcpy(dest, light, sizeof(t_light));
	ft_memcpy(dest + sizeof(t_light), actual_light, sizeof_actuallight);
}

static void		update_light_buffer_offsets(void *lightbuffer,
unsigned int offset, size_t size_to_update)
{
	t_light			*light;
	unsigned int	step;
	unsigned int	init_offset;

	init_offset = offset;
	while (size_to_update > 0)
	{
		light = (t_light*)(lightbuffer + (offset - init_offset));
		light->buffer_offset = offset;
		step = sizeof(t_light) + light_sizeof(light->lighttype);
		size_to_update -= step;
		offset += step;
	}
}

inline size_t	light_sizeof(t_light_type type)
{
	if (type == DIRLIGHT)
		return (sizeof(t_dirlight));
	else if (type == POINTLIGHT)
		return (sizeof(t_pointlight));
	else if (type == SPOTLIGHT)
		return (sizeof(t_spotlight));
	assert(FALSE && "Light structure instance should have lighttype field");
	return (0);
}

void			scene_remove_light(t_scene *scene,
const t_light *light)
{
	void	*dest;
	void	*after_light_ptr;
	size_t	after_light_size;
	size_t	sizeof_actuallight;

	sizeof_actuallight = light_sizeof(light->lighttype);
	dest = scene->host_lightbuffer + light->buffer_offset;
	after_light_ptr = dest + sizeof(t_light) + sizeof_actuallight;
	after_light_size = scene->lightbuffer_size
	- (after_light_ptr - scene->host_lightbuffer);
	ft_memcpy(dest, after_light_ptr, after_light_size);
	update_light_buffer_offsets(dest, dest - scene->host_lightbuffer,
	after_light_size);
	scene->lightbuffer_size -= sizeof(t_light) + sizeof_actuallight;
	scene->nlights--;
}

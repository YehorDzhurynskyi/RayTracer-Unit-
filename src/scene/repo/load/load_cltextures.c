/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cltextures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

cl_image_format	texture_array_image_format(void)
{
	cl_image_format	format;

	format.image_channel_order = CL_RGBA;
	format.image_channel_data_type = CL_UNORM_INT8;
	return (format);
}

cl_image_desc	texture_array_image_desc(int width,
int height, int arr_size)
{
	cl_image_desc	desc;

	desc.image_type = CL_MEM_OBJECT_IMAGE2D_ARRAY;
	desc.image_width = width;
	desc.image_height = height;
	desc.image_array_size = arr_size;
	desc.image_row_pitch = 0;
	desc.image_slice_pitch = 0;
	desc.num_mip_levels = 0;
	desc.num_samples = 0;
	desc.buffer = NULL;
	return (desc);
}

static cl_mem	null_cltextures(void)
{
	return (create_image(texture_array_image_format(),
	texture_array_image_desc(1, 1, 1), (unsigned int[]){0x0}));
}

static void		upload_pixels_on_device(t_scene *scene, void *pixels)
{
	SDL_Surface	*surface;
	char		path[2048];
	int			i;

	i = -1;
	while (++i < (int)scene->texture_map.data.size)
	{
		ft_strncpy(path, TEXTURE_DIR, 2048);
		ft_strlcat(path, texture_map_at(&scene->texture_map, i), 2048);
		surface = create_surface(path);
		ft_memcpy(pixels + TEXTURE_SIZE * i, surface->pixels, TEXTURE_SIZE);
		SDL_FreeSurface(surface);
	}
	scene->textures = create_image(texture_array_image_format(),
	texture_array_image_desc(TEXTURE_DIMENSION, TEXTURE_DIMENSION,
	scene->texture_map.data.size), pixels);
}

void			load_cltextures(t_scene *scene)
{
	void	*pixels;

	if (scene->texture_map.data.size == 0)
	{
		scene->textures = null_cltextures();
		return ;
	}
	pixels = malloc(TEXTURE_SIZE * scene->texture_map.data.size);
	if (pixels == NULL)
	{
		log_error("Failed to allocate memory for textures", RT_MEM_ALLOC_ERROR);
		scene->textures = null_cltextures();
		return ;
	}
	upload_pixels_on_device(scene, pixels);
	free(pixels);
}

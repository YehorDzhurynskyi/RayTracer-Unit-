/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "gui.h"
#include <dirent.h>
#include "logger.h"

static cl_image_format	image_format(void)
{
	cl_image_format	format;

	format.image_channel_order = CL_RGBA;
	format.image_channel_data_type = CL_UNORM_INT8;
	return (format);
}

static cl_image_desc	image_desc(const SDL_Surface *surface)
{
	cl_image_desc	desc;

	desc.image_type = CL_MEM_OBJECT_IMAGE2D_ARRAY;
	desc.image_width = surface->w;
	desc.image_height = surface->h;
	desc.image_array_size = 6;
	desc.image_row_pitch = 0;
	desc.image_slice_pitch = 0;
	desc.num_mip_levels = 0;
	desc.num_samples = 0;
	desc.buffer = NULL;
	return (desc);
}

static void	load_skybox_surfaces(const char *dirname, SDL_Surface **surfaces)
{
	char			path[RT_GUI_RESOURCE_PATH_BUFF_LEN];
	DIR				*dir;
	struct dirent	*ent;
	size_t			dir_offset;
	int				i;

	// TODO: validate
	// every textures should have special names and same size
	ft_strncpy(path, SKYBOX_DIR, RT_GUI_RESOURCE_PATH_BUFF_LEN);
	ft_strlcat(path, dirname, RT_GUI_RESOURCE_PATH_BUFF_LEN);
	ft_strlcat(path, "/", RT_GUI_RESOURCE_PATH_BUFF_LEN);
	dir_offset = ft_strlen(path);
	dir = opendir(path);
	i = 0;
	while((ent = readdir(dir)) != NULL)
	{
		if (ft_str_ends_with(ent->d_name, ".jpg") || ft_str_ends_with(ent->d_name, ".JPG")
		|| ft_str_ends_with(ent->d_name, ".jpeg") || ft_str_ends_with(ent->d_name, ".JPEG")
		|| ft_str_ends_with(ent->d_name, ".png") || ft_str_ends_with(ent->d_name, ".PNG"))
		{
			ft_strncpy(path + dir_offset, ent->d_name, RT_GUI_RESOURCE_PATH_BUFF_LEN - dir_offset);
			surfaces[i] = load_surface(path);
			i++;
		}
	}
	closedir(dir);
}

#include <assert.h>

cl_mem	load_skybox(const char *dirname)
{
	SDL_Surface		*surfaces[6];
	void			*pixels;
	int				i;
	int				err;
	cl_image_format	format;
	cl_image_desc	desc;
	cl_mem			mem_obj;

	assert(dirname != NULL);
	load_skybox_surfaces(dirname, surfaces);
	format = image_format();
	desc = image_desc(surfaces[0]);
	pixels = malloc(6 * 4 * desc.image_width * desc.image_height);
	i = 0;
	while (i < 6)
	{
		SDL_LockSurface(surfaces[i]);
		ft_memcpy(pixels + i * (desc.image_width * 4 * desc.image_height), surfaces[i]->pixels, desc.image_width * 4 * desc.image_height);
		SDL_UnlockSurface(surfaces[i]);
		i++;
	}
	mem_obj = clCreateImage(g_clcontext.context, CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
	&format, &desc, pixels, &err);
	if (err != CL_SUCCESS)
		log_error(opencl_get_error(err), RT_OPENCL_ERROR);
	free(pixels);
	i = 0;
	while (i < 6)
		SDL_FreeSurface(surfaces[i++]);
	return (mem_obj);
}

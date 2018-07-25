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

static cl_image_format	skybox_image_format(void)
{
	cl_image_format	format;

	format.image_channel_order = CL_RGBA;
	format.image_channel_data_type = CL_UNORM_INT8;
	return (format);
}

static cl_image_desc	skybox_image_desc(int width, int height, int arr_size)
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

static cl_mem	null_skybox(void)
{
	return (create_climage(skybox_image_format(), skybox_image_desc(1, 1, 1), (unsigned int[]){0x0}));
}

cl_mem	load_skybox(const char *dirname)
{
	SDL_Surface	*surfaces[6];
	void		*pixels;
	int			i;
	cl_mem		mem_obj;
	size_t		tex_size;

	if (dirname == NULL)
		return (null_skybox());
	load_skybox_surfaces(dirname, surfaces);
	tex_size = 4 * surfaces[0]->w * surfaces[0]->h;
	pixels = malloc(6 * tex_size);
	i = -1;
	while (++i < 6)
	{
		SDL_LockSurface(surfaces[i]);
		ft_memcpy(pixels + i * tex_size, surfaces[i]->pixels, tex_size);
		SDL_UnlockSurface(surfaces[i]);
	}
	mem_obj = create_climage(skybox_image_format(), skybox_image_desc(surfaces[0]->w, surfaces[0]->h, 6), pixels);
	free(pixels);
	i = 0;
	while (i < 6)
		SDL_FreeSurface(surfaces[i++]);
	return (mem_obj);
}

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

static t_bool	valid_image_format(const char *name)
{
	return (ft_str_ends_with(name, ".jpg")
	|| ft_str_ends_with(name, ".JPG")
	|| ft_str_ends_with(name, ".jpeg")
	|| ft_str_ends_with(name, ".JPEG")
	|| ft_str_ends_with(name, ".png")
	|| ft_str_ends_with(name, ".PNG"));
}

static t_bool	load_skybox_surfaces(const char *dirname,
SDL_Surface **surfaces)
{
	char			path[RT_GUI_RESOURCE_PATH_BUFF_LEN];
	DIR				*dir;
	struct dirent	*ent;
	size_t			dir_offset;
	int				i;

	ft_strncpy(path, SKYBOX_DIR, RT_GUI_RESOURCE_PATH_BUFF_LEN);
	ft_strlcat(path, dirname, RT_GUI_RESOURCE_PATH_BUFF_LEN);
	ft_strlcat(path, "/", RT_GUI_RESOURCE_PATH_BUFF_LEN);
	dir_offset = ft_strlen(path);
	if ((dir = opendir(path)) == NULL)
		return (FALSE);
	i = 0;
	while ((ent = readdir(dir)) != NULL)
	{
		if (valid_image_format(ent->d_name))
		{
			ft_strncpy(path + dir_offset, ent->d_name,
			RT_GUI_RESOURCE_PATH_BUFF_LEN - dir_offset);
			surfaces[i] = create_surface(path);
			i++;
		}
	}
	closedir(dir);
	return (TRUE);
}

static void		cleanup_host_resources(SDL_Surface *surfaces[6], void *pixels)
{
	int	i;

	i = 0;
	while (i < 6)
		SDL_FreeSurface(surfaces[i++]);
	free(pixels);
}

cl_mem			load_skybox(const char *dirname)
{
	SDL_Surface	*surfaces[6];
	void		*pixels;
	int			i;
	cl_mem		mem_obj;
	size_t		tex_size;

	if (dirname == NULL || load_skybox_surfaces(dirname, surfaces) == FALSE)
	{
		return (create_image(texture_array_image_format(),
		texture_array_image_desc(1, 1, 1), (unsigned int[]){0x0}));
	}
	tex_size = 4 * surfaces[0]->w * surfaces[0]->h;
	pixels = malloc(6 * tex_size);
	i = -1;
	while (++i < 6)
	{
		SDL_LockSurface(surfaces[i]);
		ft_memcpy(pixels + i * tex_size, surfaces[i]->pixels, tex_size);
		SDL_UnlockSurface(surfaces[i]);
	}
	mem_obj = create_image(texture_array_image_format(),
	texture_array_image_desc(surfaces[0]->w, surfaces[0]->h, 6), pixels);
	cleanup_host_resources(surfaces, pixels);
	return (mem_obj);
}

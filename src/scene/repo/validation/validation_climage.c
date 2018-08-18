/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_climage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define IMG_TIP		", uri should be name of file in assets/textures folder"
#define IMG_LOAD_MSG	"Failed to read texture by uri" IMG_TIP
#define IMG_DIMEN_MSG	"Texture has wrong dimension, it should be 256x256"

t_err_code	validate_climage_texture(const t_cson *cson)
{
	t_err_code	err;
	const char	*uri;
	char		path[2048];
	SDL_Surface	*surface;

	err = validate_string_required(cson, CSON_URI_KEY);
	uri = cson_get_string(cson_valueof(cson, CSON_URI_KEY));
	if (uri != NULL)
	{
		ft_strncpy(path, TEXTURE_DIR, 2048);
		ft_strlcat(path, uri, 2048);
		surface = create_surface(path);
		if (surface == NULL)
			err |= validation_failed_parent(cson, CSON_URI_KEY,
			RT_RESOURCE_LOADING_ERROR, IMG_LOAD_MSG);
		else if (surface->w != TEXTURE_DIMENSION
		|| surface->h != TEXTURE_DIMENSION)
			err |= validation_failed_parent(cson, CSON_URI_KEY,
			RT_WRONG_DIMENSION_ERROR, IMG_DIMEN_MSG);
		SDL_FreeSurface(surface);
	}
	return (err);
}

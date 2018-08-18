/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include <SDL_image.h>

SDL_Surface	*create_surface(const char *path)
{
	SDL_Surface	*surface;
	SDL_Surface	*converted_surface;

	surface = IMG_Load(path);
	if (surface == NULL)
		return (NULL);
	converted_surface = SDL_ConvertSurfaceFormat(surface,
	SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(surface);
	return (converted_surface);
}

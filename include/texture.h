/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "opencl.h"
# include <SDL.h>

# define TEXTURE_DIMENSION	256
# define TEXTURE_SIZE		(TEXTURE_DIMENSION * TEXTURE_DIMENSION * 4)

typedef enum
{
	CHESS = 1,
	CLIMAGE
}	t_texture_type;

typedef struct s_texture	t_texture;
struct __attribute__ ((packed))	s_texture
{
	t_claddress		addr;
	t_clscalar		scale;
	t_clscalar		u_offset;
	t_clscalar		v_offset;
	t_texture_type	texture_type;
};

typedef struct s_chess_texture	t_chess_texture;
struct __attribute__ ((packed))	s_chess_texture
{
	t_clcolor		color1;
	t_clcolor		color2;
};

typedef struct s_climage_texture	t_climage_texture;
struct __attribute__ ((packed))	s_climage_texture
{
	cl_int			tex_index;
};

SDL_Surface	*create_surface(const char *path);
cl_mem		create_image(const cl_image_format format,
const cl_image_desc desc, void *pixels);

typedef struct s_texture_map	t_texture_map;
struct	s_texture_map
{
	t_alst	data;
};

t_texture_map	texture_map_create(int capacity);
const char		*texture_map_at(const t_texture_map *map, int index);
void			texture_map_add(t_texture_map *map, const char *value);
void			texture_map_cleanup(t_texture_map *map);

extern const char	*g_texture_captions[];

#endif

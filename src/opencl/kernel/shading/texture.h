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

typedef enum
{
	CHESS = 1,
	CLIMAGE
}	t_texture_type;

typedef struct s_texture	t_texture;
struct __attribute__ ((packed))	s_texture
{
	t_address		addr;
	t_scalar		scale;
	t_scalar		u_offset;
	t_scalar		v_offset;
	t_texture_type	texture_type;
};

typedef struct s_chess_texture	t_chess_texture;
struct __attribute__ ((packed))	s_chess_texture
{
	t_color			color1;
	t_color			color2;
};

typedef struct s_climage_texture	t_climage_texture;
struct __attribute__ ((packed))	s_climage_texture
{
	int				tex_index;
};

t_rcolor	texture_map(const t_scene_buffers *buffers, __read_only image2d_array_t textures,
t_address tex_addr, t_scalar u, t_scalar v);
t_vec4		normal_map(const t_vec4 normal, const t_vec4 new_normal);

#endif

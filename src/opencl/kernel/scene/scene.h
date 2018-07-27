/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef enum
{
	NOAA = 1,
	SSAAx4,
	SSAAx8
}	t_aa;

typedef struct	__attribute__ ((packed))
{
	int			trace_depth;
	t_aa		aa;
	t_bool		global_illumination_enabled;
	t_scalar	ambient;
	t_scalar	fov;
	t_address	selected_shape_addr;
}	t_scene_config;

typedef struct	__attribute__ ((packed))
{
	t_mat4x4	orientation;
	t_vec4		position;
}	t_camera;

typedef struct			__attribute__ ((packed))
{
	int					nshapes;
	uint				shapes_size;
	int					nlightsources;
	uint				lightsources_size;
	int					nmaterials;
	uint				materials_size;
	int					ntextures;
	uint				textures_size;
}	t_scenebuffer_meta;

typedef struct
{
	__constant t_byte	*shapebuffer;
	__constant t_byte	*lightsourcebuffer;
	__constant t_byte	*materialbuffer;
	__constant t_byte	*texturebuffer;
}	t_scene_buffers;

typedef struct
{
	t_scene_config		config;
	t_scenebuffer_meta	meta;
	t_camera			camera;
	int					x;
	int					y;
	int					width;
	int					height;
}	t_scene;

#endif

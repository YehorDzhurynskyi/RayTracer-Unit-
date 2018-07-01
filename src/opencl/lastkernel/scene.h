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
	t_bool		global_illumination;
	t_scalar	ambient;
	t_scalar	fov;
}	t_scene_config;

typedef struct	__attribute__ ((packed))
{
	t_mat4x4	orientation;
	t_vec3		position;
}	t_camera;

typedef struct			__attribute__ ((packed))
{
	int					nshapes;
	size_t				shapes_size;
	int					nlightsources;
	size_t				lightsources_size;
	int					nmaterials;
	size_t				materials_size;
}	t_scenebuffer_meta;

typedef struct
{
	__constant t_byte	*shapebuffer;
	__constant t_byte	*lightsourcebuffer;
	__constant t_byte	*materialbuffer;
	t_scene_config		config;
	t_scenebuffer_meta	meta;
	t_camera			camera;
}	t_scene;

#endif

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

# include "camera.h"
# include "shape.h"
# include "lightsource.h"
# include "material.h"
# include "texture.h"

# define SHAPEBUFF_CAPACITY			1024 * 12
# define LIGHTSOURCEBUFF_CAPACITY	1024 * 4
# define MATERIALBUFF_CAPACITY		1024 * 1
# define TEXTUREBUFF_CAPACITY		1024 * 1

# define SCENE_DIR		RT_CWD "/assets/scenes/"
# define SKYBOX_DIR		RT_CWD "/assets/skyboxes/"
# define TEXTURE_DIR	RT_CWD "/assets/textures/"

# define NONE_SELECTED_ADDR	-1

# define NONE_SELECTED_ADDR	-1

typedef enum
{
	NONE_TARGET = 0,
	SHAPEBUFF_TARGET,
	LIGHTSOURCEBUFF_TARGET,
	MATERIALBUFF_TARGET,
	TEXTUREBUFF_TARGET
}	t_buff_target;

typedef enum
{
	NOAA = 1,
	SSAAx4,
	SSAAx8
}	t_aa;

typedef struct			__attribute__ ((packed))
{
	cl_int				trace_depth;
	t_aa				aa;
	t_clbool			global_illumination_enabled;
	t_clscalar			ambient;
	t_clscalar			fov;
	t_claddress			selected_shape_addr;
}	t_scene_config;

typedef struct			__attribute__ ((packed))
{
	cl_int				nshapes;
	cl_uint				shapes_size;
	cl_int				nlightsources;
	cl_uint				lightsources_size;
	cl_int				nmaterials;
	cl_uint				materials_size;
	cl_int				ntextures;
	cl_uint				textures_size;
}	t_scene_meta;

typedef struct
{
	cl_mem				device_shapebuffer;
	void				*host_shapebuffer;
	cl_mem				device_lightsourcebuffer;
	void				*host_lightsourcebuffer;
	cl_mem				device_materialbuffer;
	void				*host_materialbuffer;
	cl_mem				device_texturebuffer;
	void				*host_texturebuffer;
	void				*mapped_device_buffer;
	void				*mapped_host_buffer;
	t_scene_config		config;
	t_scene_meta		meta;
	t_camera			camera;
	cl_mem				skybox;
	cl_mem				textures;
	t_texture_map		texture_map;
}	t_scene;

void					scene_init_memory(void);
void					scene_rewind(t_scene *scene);
void					scene_cleanup(void);
void					scene_change(const char *scene_name);

extern t_scene			g_main_scene;

#endif

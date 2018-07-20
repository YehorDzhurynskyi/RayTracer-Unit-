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

# ifndef SHAPEBUFF_CAPACITY
#  define SHAPEBUFF_CAPACITY	1024 * 12
# endif

# ifndef LIGHTSOURCEBUFF_CAPACITY
#  define LIGHTSOURCEBUFF_CAPACITY	1024 * 4
# endif

# ifndef MATERIALBUFF_CAPACITY
#  define MATERIALBUFF_CAPACITY	1024 * 1
# endif

# define SCENE_DIR	RT_CWD "/scenes/"

# define NONE_SELECTED_ADDR	-1

typedef enum
{
	NONE_TARGET = 0,
	SHAPEBUFF_TARGET,
	LIGHTSOURCEBUFF_TARGET,
	MATERIALBUFF_TARGET
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
	t_clbool			global_illumination;
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
}	t_scenebuffer_meta;

typedef struct
{
	cl_mem				device_shapebuffer;
	void				*host_shapebuffer;
	cl_mem				device_lightsourcebuffer;
	void				*host_lightsourcebuffer;
	cl_mem				device_materialbuffer;
	void				*host_materialbuffer;
	void				*mapped_device_buffer;
	void				*mapped_host_buffer;
	t_scene_config		config;
	t_scenebuffer_meta	meta;
	t_camera			camera;
}	t_scene;

t_scene					scene_create(void);
void					scene_cleanup(t_scene *scene);
void					scene_change(const char *scene_name);

extern t_scene			*g_main_scene_ptr;

#endif

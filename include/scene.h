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

# include "ft.h"
# include "shape.h"
# include "light.h"

# ifndef SHAPEBUFFER_CAPACITY
#  define SHAPEBUFFER_CAPACITY	1024 * 16
# endif

# ifndef LIGHTBUFFER_CAPACITY
#  define LIGHTBUFFER_CAPACITY	1024 * 4
# endif

typedef struct	__attribute__ ((packed)) s_camera
{
	t_clmat4x4		rotation_matrix;
	t_clvec4		position;
}	t_camera;

typedef struct
{
	cl_mem			shapebuffer;
	void			*host_shapebuffer;
	size_t			shapebuffer_size;
	unsigned int	nshapes;
	cl_mem			lightbuffer;
	void			*host_lightbuffer;
	size_t			lightbuffer_size;
	unsigned int	nlights;
	t_camera		camera;
	cl_float		ambient;
	// cube map texture
}	t_scene;

typedef enum
{
	SHAPE_BUFFER_TARGET = 1,
	LIGHT_BUFFER_TARGET
}	t_buffer_target;

t_camera			camera_look_at(const t_vec3d *position,
const t_vec3d *spot, const t_vec3d *up);
t_camera			camera_create(const t_vec3d *position,
const t_vec3d *forward, const t_vec3d *right, const t_vec3d *up);

t_scene				scene_create(void);
void				scene_cleanup(t_scene *scene);
void				scene_unmap(t_scene *scene, t_buffer_target target);
size_t				shape_sizeof(t_shape_type type);
size_t				light_sizeof(t_light_type type);

#endif

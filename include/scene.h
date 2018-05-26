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

# include "shape.h"

typedef struct	__attribute__ ((packed)) s_camera
{
	t_clmat4x4	rotation_matrix;
	t_clvec4	position;
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
	// cube map texture
}	t_scene;

typedef enum
{
	SHAPE_BUFFER_TARGET = 1,
	LIGHT_BUFFER_TARGET
}	t_buffer_target;

t_scene	scene_create(void);
void	scene_cleanup(t_scene *scene);
void	scene_unmap(t_scene *scene, t_buffer_target target);

void	scene_add_sphere(t_scene *scene, t_shape *shape, const t_sphere *sphere);
void	scene_update_sphere(t_scene *scene, const t_shape *shape, const t_sphere *sphere);

void	scene_add_plane(t_scene *scene, t_shape *shape, const t_plane *plane);
void	scene_update_plane(t_scene *scene, const t_shape *shape, const t_plane *plane);

void	scene_add_cylinder(t_scene *scene, t_shape *shape, const t_cylinder *cylinder);
void	scene_update_cylinder(t_scene *scene, const t_shape *shape, const t_cylinder *cylinder);

void	scene_add_cone(t_scene *scene, t_shape *shape, const t_cone *cone);
void	scene_update_cone(t_scene *scene, const t_shape *shape, const t_cone *cone);

void	scene_remove(t_scene *scene, const t_shape *shape);

#endif

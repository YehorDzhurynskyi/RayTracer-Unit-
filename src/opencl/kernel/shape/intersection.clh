/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

__constant t_shape	*cast_ray(const t_scene *scene,
const t_scene_buffers *buffers, const t_ray *ray, t_scalar *nearest_t);

__constant t_lightsource	*cast_lightsource_ray(const t_scene *scene,
const t_scene_buffers *buffers, const t_ray *ray, t_scalar *nearest_t);

__constant t_shape	*shape_intersected(__constant t_shape *shape, const t_ray *ray, t_scalar *t);
int					primitive_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2);

int					plane_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t);
int					sphere_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2);
int					cylinder_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2);
int					cone_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2);
int					torus_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2);
int					quadric_surface_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2);
int					parallelepiped_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t1, t_scalar *t2);

#endif

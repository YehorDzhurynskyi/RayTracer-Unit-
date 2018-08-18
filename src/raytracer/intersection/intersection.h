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

# include "raytracer.h"

const t_shape	*shape_intersected(const t_shape *shape,
const t_ray *ray, float *t);
int				primitive_intersected(const t_shape *shape,
const t_ray *ray, float *t1, float *t2);

int				plane_intersected(const t_primitive *primitive,
const t_ray *ray, float *t);
int				sphere_intersected(const t_primitive *primitive,
const t_ray *ray, float *t1, float *t2);
int				cylinder_intersected(const t_primitive *primitive,
const t_ray *ray, float *t1, float *t2);
int				cone_intersected(const t_primitive *primitive,
const t_ray *ray, float *t1, float *t2);

t_bool			limit(const t_primitive *primitive,
const t_ray *ray, float *target_t, const float t);

#endif

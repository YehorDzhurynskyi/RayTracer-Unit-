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

t_bool	shape_intersected(const t_shape *shape, const t_ray *ray, float *t);
t_bool	primitive_intersected(const t_primitive *primitive, const t_ray *ray, float *t);

t_bool	plane_intersected(const t_primitive *primitive, const t_ray *ray, float *t);
t_bool	sphere_intersected(const t_primitive *primitive, const t_ray *ray, float *t);
t_bool	cylinder_intersected(const t_primitive *primitive, const t_ray *ray, float *t);
t_bool	cone_intersected(const t_primitive *primitive, const t_ray *ray, float *t);

#endif

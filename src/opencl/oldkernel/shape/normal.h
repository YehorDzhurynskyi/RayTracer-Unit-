/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMAL_H
# define NORMAL_H

t_vec4	obtain_normal(const t_vec4 *point, __constant t_shape *shape);
t_vec4	obtain_primitive_normal(const t_vec4 *point, __constant t_primitive *primitive);

t_vec4	obtain_sphere_normal(const t_vec4 *point, __constant t_primitive *primitive);
t_vec4	obtain_plane_normal(const t_vec4 *point, __constant t_primitive *primitive);
t_vec4	obtain_cone_normal(const t_vec4 *point, __constant t_primitive *primitive);
t_vec4	obtain_cylinder_normal(const t_vec4 *point, __constant t_primitive *primitive);

#endif

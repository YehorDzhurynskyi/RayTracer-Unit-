/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

t_vec3	mat4x4_mult_vec3(const t_mat4x4 mat, const t_vec3 vec);
t_vec4	mat4x4_mult_vec4(const t_mat4x4 mat, const t_vec4 vec);

t_vec3	reflect3(const t_vec3 incident, const t_vec3 normal);
t_vec4	reflect4(const t_vec4 incident, const t_vec4 normal);

t_vec3	refract3(t_vec3 incident, t_vec3 normal, t_scalar ior);
t_vec4	refract4(t_vec4 incident, t_vec4 normal, t_scalar ior);

#endif

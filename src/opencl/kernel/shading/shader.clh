/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

typedef struct s_fragment	t_fragment;
struct			s_fragment
{
	t_vec4		point;
	t_vec4		normal;
	t_vec4		to_origin;
	t_rcolor	diffuse_albedo;
	t_rcolor	specular_albedo;
	t_scalar	glossiness;
	t_scalar	ior;
};

t_rcolor		shade(const t_scene *scene, const t_scene_buffers *buffers,
__read_only image2d_array_t textures, const t_fragment *fragment);
void			obtain_uv(__constant t_primitive *primitive,
const t_fragment *fragment, t_scalar *u, t_scalar *v);
t_fragment		compose_fragment(const t_scene_buffers *buffers,
__read_only image2d_array_t textures, __constant t_shape *shape, const t_ray *ray, t_scalar t);

#endif

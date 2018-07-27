/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# define DEFAULT_MATERIAL_ID	-1

typedef union
{
	t_scalar			value;
	t_address			tex_addr;
}	t_scalar_variant;

typedef union
{
	t_color				color;
	t_address			tex_addr;
}	t_color_variant;

typedef int				t_material_mask;

typedef struct			__attribute__ ((packed))
{
	t_address			addr;
	t_material_mask		mask;
	t_color_variant		diffuse_albedo;
	t_color_variant		specular_albedo;
	t_scalar_variant	glossiness;
	t_scalar			ior;
	t_address			normal_map;
}	t_material;

# define DIFFUSE_MASK		(1 << 0)
# define SPECULAR_MASK		(1 << 1)
# define GLOSSINESS_MASK	(1 << 2)
# define NORMAL_MAP_MASK	(1 << 3)

# define DIFFUSE_IS_TEX(mask)		(mask & DIFFUSE_MASK)
# define SPECULAR_IS_TEX(mask)		(mask & SPECULAR_MASK)
# define GLOSSINESS_IS_TEX(mask)	(mask & GLOSSINESS_MASK)
# define HAS_NORMAL_MAP(mask)		(mask & NORMAL_MAP_MASK)

__constant t_material	*get_material(const t_scene_buffers *buffers, __constant t_shape *shape);
t_scalar				get_opacity(t_color color);

#endif

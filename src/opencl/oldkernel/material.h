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
	t_scalar		value;
	t_resourceid	id;
}	t_variant;

typedef struct		__attribute__ ((packed))
{
	t_address		addr;
	t_color			color;
	t_variant		specularity;
	t_variant		glossiness;
	t_scalar		ior;
	t_resourceid	normal_map;
	t_resourceid	albedo_map;
}	t_material;

t_scalar			get_opacity(t_color color);
__constant t_material	*get_material(const t_scene *scene, __constant t_shape *shape);

#endif

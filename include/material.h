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

# include "opencl.h"

# define DEFAULT_MATERIAL_ID	-1

typedef union
{
	t_clscalar		value;
	t_clresourceid	res_id;
}	t_scalar_variant;

typedef union
{
	t_clcolor		color;
	t_clresourceid	res_id;
}	t_color_variant;

typedef struct		__attribute__ ((packed))
{
	t_claddress			addr;
	t_color_variant		diffuse_albedo;
	t_color_variant		specular_albedo;
	t_scalar_variant	glossiness;
	t_clscalar			ior;
	t_clresourceid		normal_map;
}	t_material;

#endif

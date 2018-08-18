/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_material	scenebuffer_default_material(void)
{
	t_material	material;

	material.mask = 0;
	material.diffuse_albedo.color = (t_clcolor){{0x0, 0x0, 0x0, 0x0}};
	material.specular_albedo.color = (t_clcolor){{0x0, 0x0, 0x0, 0x0}};
	material.glossiness.value = 0.0f;
	material.ior = 1.0f;
	return (material);
}

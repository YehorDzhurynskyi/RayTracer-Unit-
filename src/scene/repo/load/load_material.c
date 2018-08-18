/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_materials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

void	load_material(t_scene *scene, const t_cson *cson)
{
	t_material	material;

	material = deserialize_material(cson);
	scenebuffer_add_material(scene, &material);
}

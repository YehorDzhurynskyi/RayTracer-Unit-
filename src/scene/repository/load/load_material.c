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

#include "scenerepository.h"
#include "sceneeditor.h"

t_err_code	load_material(t_scene *scene, const t_cson *cson)
{
	t_err_code	err;
	t_material	material;

	if (cson == NULL)
		return (RT_VALUE_PARSING_ERROR);
	if (cson_is_object(cson) == FALSE)
		return (RT_WRONG_VALUE_FORMAT_ERROR);
	err = RT_NO_ERROR;
	material = deserialize_material(cson, &err);
	scenebuffer_add_material(scene, &material);
	return (err);
}

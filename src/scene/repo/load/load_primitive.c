/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

static void	load_actual_limitation(t_scene *scene, const t_cson *cson,
int target, t_limitation *limitation)
{
	const void	*actual_limitation;

	actual_limitation = NULL;
	if (IS_AXIAL(limitation->limitation_type))
		actual_limitation = (t_axial_limitation[]){deserialize_axial_limitation(cson)};
	scenebuffer_add_limitation(scene, limitation, actual_limitation, target);
}

static void	load_actual_primitive(t_scene *scene, const t_cson *cson,
int target, t_primitive *primitive)
{
	const void	*actual_primitive;

	if (primitive->primitive_type == SPHERE)
		actual_primitive = (t_sphere[]){deserialize_sphere(cson)};
	else if (primitive->primitive_type == CYLINDER)
		actual_primitive = (t_cylinder[]){deserialize_cylinder(cson)};
	else if (primitive->primitive_type == CONE)
		actual_primitive = (t_cone[]){deserialize_cone(cson)};
	else if (ZERO_SIZE_PRIMITIVE(primitive->primitive_type))
		actual_primitive = NULL;
	scenebuffer_add_primitive(scene, primitive, actual_primitive, target);
}

static void	load_limitations(t_scene *scene,
const t_cson *limitations_cson, int target)
{
	int				count;
	int				i;
	const t_cson	*limitation_cson;
	t_limitation	limitation;

	count = cson_size(limitations_cson);
	i = 0;
	while (i < count)
	{
		limitation_cson = cson_at(limitations_cson, i++);
		limitation = deserialize_limitation(limitation_cson);
		load_actual_limitation(scene, limitation_cson, target, &limitation);
	}
}

void			load_primitive(t_scene *scene, const t_cson *cson, int target)
{
	t_primitive		primitive;
	const t_cson	*limitations_cson;

	primitive = deserialize_primitive(cson);
	limitations_cson = cson_valueof(cson, CSON_LIMITATIONS_KEY);
	primitive.nlimitations = limitations_cson == NULL ? 0 : cson_size(limitations_cson);
	load_actual_primitive(scene, cson, target, &primitive);
	if (limitations_cson != NULL)
		load_limitations(scene, limitations_cson, target);
}

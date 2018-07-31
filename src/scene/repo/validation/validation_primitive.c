/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_primitive.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TYPE_TIP_MSG	", it should be primitive-type string"
#define TYPE_ABSENT_MSG	"The primitive type is absent" TYPE_TIP_MSG
#define TYPE_TYPE_MSG	"The primitive type can't be recognized" TYPE_TIP_MSG
#define TYPE_FORMAT_MSG	"Primitive type isn't string" TYPE_TIP_MSG

#define TIP_MSG		", it should be object"
#define ABSENT_MSG	"Primitive is absent" TIP_MSG
#define FORMAT_MSG	"Primitive isn't object" TIP_MSG

t_err_code			validate_cone(const t_cson *cson)
{	
	return (validate_real_required_ranged(cson, CSON_ANGLE_KEY, (double[2]){1.0f, 179.0f}));
}

t_err_code			validate_cylinder(const t_cson *cson)
{
	return (validate_real_required(cson, CSON_RADIUS_KEY));
}

t_err_code			validate_sphere(const t_cson *cson)
{
	return (validate_real_required(cson, CSON_RADIUS_KEY));
}

static t_err_code	validate_primitive_type(const t_cson *cson)
{
	const t_cson	*type_cson;
	const char		*type;

	type_cson = cson_valueof(cson, CSON_TYPE_KEY);
	if (type_cson == NULL)
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, TYPE_ABSENT_MSG));
	if (cson_is_string(type_cson) == FALSE)
		return (validation_failed(type_cson, RT_WRONG_VALUE_FORMAT_ERROR, TYPE_FORMAT_MSG));
	type = cson_get_string(type_cson);
	if (ft_strequ(type, CSON_SHAPE_COMPOSITE)
	|| ft_strequ(type, CSON_SHAPE_POINT)
	|| ft_strequ(type, CSON_SHAPE_SPHERE)
	|| ft_strequ(type, CSON_SHAPE_PLANE)
	|| ft_strequ(type, CSON_SHAPE_CONE)
	|| ft_strequ(type, CSON_SHAPE_CYLINDER))
		return (RT_NO_ERROR);
	return (validation_failed(type_cson, RT_WRONG_VALUE_TYPE_ERROR, TYPE_TYPE_MSG));
}

t_err_code			validate_primitive(const t_cson *cson)
{
	t_err_code		err;
	const char		*type;
	const t_cson	*primitive_cson;

	primitive_cson = cson_valueof(cson, CSON_PRIMITIVE_KEY);
	if (primitive_cson == NULL)
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, ABSENT_MSG));
	if (cson_is_object(primitive_cson) == FALSE)
		return (validation_failed(primitive_cson, RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	err = validate_primitive_type(primitive_cson);
	err |= validate_vec3_required(primitive_cson, CSON_POSITION_KEY, FALSE);
	err |= validate_orientation_optional(primitive_cson, CSON_ORIENTATION_KEY, "[0 0 0]");
	type = cson_get_string(cson_valueof(primitive_cson, CSON_TYPE_KEY));
	if (ft_strequ(type, CSON_SHAPE_SPHERE))
		err |= validate_sphere(primitive_cson);
	else if (ft_strequ(type, CSON_SHAPE_CONE))
		err |= validate_cone(primitive_cson);
	else if (ft_strequ(type, CSON_SHAPE_CYLINDER))
		err |= validate_cylinder(primitive_cson);
	err |= validate_limitations(cson_valueof(primitive_cson, CSON_LIMITATIONS_KEY));
	return (err);
}

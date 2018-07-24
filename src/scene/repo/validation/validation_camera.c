/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TIP_MSG		", it should be object"
#define ABSENT_MSG	"Camera is absent" TIP_MSG
#define FORMAT_MSG	"Camera isn't object" TIP_MSG

t_err_code	validate_camera(const t_cson *cson)
{
	t_err_code		err;
	const t_cson	*camera_cson;

	camera_cson = cson_valueof(cson, CSON_CAMERA_KEY);
	if (camera_cson == NULL)
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, ABSENT_MSG));
	if (cson_is_object(camera_cson) == FALSE)
		return (validation_failed(camera_cson, RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	err = validate_vec3_required(camera_cson, CSON_POSITION_KEY, FALSE);
	err |= validate_vec3_required(camera_cson, CSON_UP_KEY, TRUE);
	if (cson_valueof(camera_cson, CSON_SPOT_KEY) != NULL)
	{
		err |= validate_vec3_required(camera_cson, CSON_SPOT_KEY, FALSE);
	}
	else
	{
		err |= validate_vec3_required(camera_cson, CSON_FORWARD_KEY, TRUE);
		err |= validate_vec3_required(camera_cson, CSON_RIGHT_KEY, TRUE);
	}
	return (err);
}

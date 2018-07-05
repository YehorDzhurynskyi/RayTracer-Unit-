/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
#include <assert.h>

#define SIZE	1024

static void			compose_error_message(char *dest,
const char *key, const char *message)
{
	size_t	key_length;
	size_t	message_length;

	*dest++ = '\'';
	key_length = ft_strlen(key);
	message_length = ft_strlen(message);
	assert(key_length + message_length + 2 <= SIZE);
	ft_memcpy(dest, key, key_length);
	dest += key_length;
	*dest++ = '\'';
	ft_memcpy(dest, message, message_length);
	dest += message_length;
	*dest = '\0';
}

static t_err_code	validate_vector_value(const t_cson *vec_cson,
const char *key, int mask, char *error_buffer)
{
	t_err_code	err;

	if (vec_cson == NULL)
	{
		if (mask & RT_VEC_REPO_REQUIRED)
		{
			compose_error_message(error_buffer, key, " vector is absent");
			log_error(error_buffer, RT_NO_REQUIRED_VALUE_ERROR);
			return (RT_NO_REQUIRED_VALUE_ERROR);
		}
		return (RT_NO_OPTIONAL_VALUE_ERROR);
	}
	if (cson_is_array(vec_cson) == FALSE || cson_size(vec_cson) != 3)
	{
		err = cson_is_array(vec_cson) == FALSE
		? RT_WRONG_VALUE_FORMAT_ERROR : RT_WRONG_DIMENSION_ERROR;
		compose_error_message(error_buffer, key, " invalid vector-3 represantation, "
		"it should be real-value array of size 3");
		log_error(error_buffer, err);
		return (err);
	}
	return (RT_NO_ERROR);
}

t_vec3d				deserialize_vec3d(const t_cson *cson,
const char *key, int mask, t_err_code *err)
{
	const t_cson	*vec_cson;
	char			error_buffer[SIZE + 1];
	t_vec3d			value;

	vec_cson = cson_valueof(cson, key);
	*err = validate_vector_value(vec_cson, key, mask, error_buffer);
	value.x = cson_get_real(cson_at(vec_cson, 0));
	value.y = cson_get_real(cson_at(vec_cson, 1));
	value.z = cson_get_real(cson_at(vec_cson, 2));
	if (mask & RT_VEC_REPO_NORMALIZE)
	{
		if (vec3d_length(&value) < 1.0E-6f)
		{
			*err = RT_ZERO_LENGTH_VECTOR_ERROR;
			compose_error_message(error_buffer, key, " this vector should have length > 0");
			log_error(error_buffer, *err);
		}
	}
	return (value);
}

t_clvec3			deserialize_vec3(const t_cson *cson,
const char *key, int mask, t_err_code *err)
{
	t_vec3d		vec3d;
	t_clvec3	value;

	vec3d = deserialize_vec3d(cson, key, mask, err);
	value = (t_clvec3){{vec3d.x, vec3d.y, vec3d.z}};
	return (value);
}

t_cson				*serialize_vec3(const t_clvec3 *vec)
{
	t_cson	*cson;

	cson = cson_array();
	cson_push_real(cson, vec->x);
	cson_push_real(cson, vec->y);
	cson_push_real(cson, vec->z);
	return (cson);
}

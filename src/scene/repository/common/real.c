/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real.c                                             :+:      :+:    :+:   */
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

static void	compose_notify_message(char *dest, const char *key,
const char *default_value_str)
{
	size_t	key_length;
	size_t	default_value_str_length;

	*dest++ = '\'';
	key_length = ft_strlen(key);
	default_value_str_length = ft_strlen(default_value_str);
	assert(key_length + default_value_str_length + 71 <= SIZE);
	ft_memcpy(dest, key, key_length);
	dest += key_length;
	ft_memcpy(dest, "' is absent or is not real-type"
		" value, the value is set to ", 59);
	dest += 59;
	ft_memcpy(dest, default_value_str, default_value_str_length);
	dest += default_value_str_length;
	ft_memcpy(dest, " by default", 11);
	dest += 11;
	*dest = '\0';
}

t_clscalar	deserialize_real(const t_cson *cson, const char *key,
const t_clscalar default_value, const char *default_value_str)
{
	char			notify_buffer[SIZE + 1];
	const t_cson	*value_cson;

	value_cson = cson_valueof(cson, key);
	if (value_cson == NULL || cson_is_real(value_cson) == FALSE)
	{
		compose_notify_message(notify_buffer, key, default_value_str);
		log_notify(notify_buffer);
		return (default_value);
	}
	return (cson_get_real(value_cson));
}

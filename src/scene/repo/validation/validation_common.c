/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_common.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include <assert.h>

#define SIZE	1024

static char		g_validation_buffer[SIZE];

static size_t	compose_property_name(const t_cson *cson)
{
	size_t		offset;
	const char	*key;

	if (cson->parent == NULL)
		return (0);
	offset = compose_property_name(cson->parent);
	key = cson->key == NULL ? "[]" : cson->key;
	ft_strncpy(g_validation_buffer + offset, key, SIZE - offset);
	offset += ft_strlen(key);
	ft_strncpy(g_validation_buffer + offset, ".", SIZE - offset);
	return (++offset);
}

t_err_code		validation_failed(const t_cson *cson,
t_err_code err_code, const char *message)
{
	size_t	offset;

	assert(cson != NULL);
	offset = compose_property_name(cson);
	--offset;
	ft_strncpy(g_validation_buffer + offset, ": ", SIZE - offset);
	offset += 2;
	ft_strncpy(g_validation_buffer + offset, message, SIZE - offset);
	log_error(g_validation_buffer, err_code);
	return (err_code);
}

t_err_code		validation_failed_parent(const t_cson *cson, const char *key,
t_err_code err_code, const char *message)
{
	size_t	offset;

	assert(cson != NULL);
	offset = compose_property_name(cson);
	ft_strncpy(g_validation_buffer + offset, key, SIZE - offset);
	offset += ft_strlen(key);
	ft_strncpy(g_validation_buffer + offset, ": ", SIZE - offset);
	offset += 2;
	ft_strncpy(g_validation_buffer + offset, message, SIZE - offset);
	log_error(g_validation_buffer, err_code);
	return (err_code);
}

t_err_code		validation_set_optional(const t_cson *cson,
const char *key, const char *default_value_str)
{
	size_t	offset;

	assert(cson != NULL);
	offset = compose_property_name(cson);
	ft_strncpy(g_validation_buffer + offset, key, SIZE - offset);
	offset += ft_strlen(key);
	ft_strncpy(g_validation_buffer + offset,
	": is absent, set default value = ", SIZE - offset);
	offset += 33;
	ft_strncpy(g_validation_buffer + offset, default_value_str, SIZE - offset);
	log_notify(g_validation_buffer);
	return (RT_NO_ERROR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

t_err_code	validate_material(const t_cson *cson)
{
	t_err_code	err;

	err = validate_color_requried(cson, CSON_DIFFUSE_COLOR_KEY);
	err |= validate_color_requried(cson, CSON_SPECULAR_COLOR_KEY);
	err |= validate_real_optional_ranged(cson, CSON_GLOSSINESS_KEY, (double[2]){0.0, 1.0}, GLOSSINESS_STR);
	err |= validate_real_optional(cson, CSON_IOR_KEY, IOR_STR);
	return (err);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "scenerepo.h"

t_clcolor			deserialize_color_required(const t_cson *cson)
{
	t_clcolor		color;
	unsigned int	hex;

	hex = ft_hex_atoui(cson_get_string(cson));
	color.x = (hex >> 16) & 0xFF;
	color.y = (hex >> 8) & 0xFF;
	color.z = (hex >> 0) & 0xFF;
	color.w = (hex >> 24) & 0xFF;
	return (color);
}

t_clcolor			deserialize_color_optional(const t_cson *cson,
const t_clcolor default_color)
{
	if (cson == NULL)
		return (default_color);
	return (deserialize_color_required(cson));
}

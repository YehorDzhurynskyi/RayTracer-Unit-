/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

static t_texture_type	recognize_texture_type(const char *type)
{
	if (ft_strequ(type, CSON_TEXTURE_CHESS))
		return (CHESS);
	else if (ft_strequ(type, CSON_TEXTURE_RESOURCE))
		return (CLIMAGE);
	return (0);
}

t_texture				deserialize_texture(const t_cson *cson)
{
	t_texture	texture;

	texture.scale = deserialize_real_optional(cson_valueof(cson, CSON_SCALE_KEY), SCALE);
	texture.u_offset = deserialize_real_optional(cson_valueof(cson, CSON_UOFFSET_KEY), UOFFSET);
	texture.v_offset = deserialize_real_optional(cson_valueof(cson, CSON_VOFFSET_KEY), VOFFSET);
	texture.texture_type = recognize_texture_type(cson_get_string(cson_valueof(cson, CSON_TYPE_KEY)));
	return (texture);
}

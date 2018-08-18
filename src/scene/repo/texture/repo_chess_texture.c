/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_chess_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

t_chess_texture	deserialize_chess_texture(const t_cson *cson)
{
	t_chess_texture	tex;

	tex.color1 = deserialize_color_required(cson_valueof(cson,
	CSON_COLOR1_KEY));
	tex.color2 = deserialize_color_required(cson_valueof(cson,
	CSON_COLOR2_KEY));
	return (tex);
}

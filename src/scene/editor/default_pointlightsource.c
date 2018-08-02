/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_pointlightsource.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_pointlightsource	scenebuffer_default_pointlightsource(void)
{
	t_pointlightsource	pointlightsource;
	t_vec3d				position;

	pointlightsource.attenuation = (t_clvec4){{1.0f, 0.0f, 0.0f, 0.0f}};
	position = scenebuffer_default_position();
	pointlightsource.position.x = position.x;
	pointlightsource.position.y = position.y;
	pointlightsource.position.z = position.z;
	return (pointlightsource);
}

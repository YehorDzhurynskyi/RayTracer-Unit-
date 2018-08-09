/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_spotlightsource.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_spotlightsource	scenebuffer_default_spotlightsource(void)
{
	t_spotlightsource	spotlightsource;

	spotlightsource.attenuation = (t_clvec4){{1.0f, 0.0f, 0.0f, 0.0f}};
	spotlightsource.direction = (t_clvec4){{0.0f, -1.0f, 0.0f, 0.0f}};
	spotlightsource.cosangle = cos(15.0 * M_PI / 180.0);
	return (spotlightsource);
}

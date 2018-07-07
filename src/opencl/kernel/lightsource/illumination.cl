/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_rcolor	illuminate(__constant t_lightsource *lightsrc, const t_fragment *fragment)
{
	__constant t_byte *actual = lightsource_get_actual(lightsrc);
	if (lightsrc->lightsource_type == POINTLIGHT)
		return (pointlightsource_illuminate(lightsrc, (__constant t_pointlightsource*)actual, fragment));
	else if (lightsrc->lightsource_type == DIRLIGHT)
		return (dirlightsource_illuminate(lightsrc, (__constant t_dirlightsource*)actual, fragment));
	else if (lightsrc->lightsource_type == SPOTLIGHT)
		return (spotlightsource_illuminate(lightsrc, (__constant t_spotlightsource*)actual, fragment));
	return (0);
}

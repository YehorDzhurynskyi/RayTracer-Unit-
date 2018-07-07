/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirlightsource.cl                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec4	to_dirlightsource(__constant t_dirlightsource *dirlightsrc)
{
	return (dirlightsrc->direction * -INFINITY);
}

t_bool	dirlightsource_is_in_shadow(void)
{
	return (TRUE);
}

t_rcolor	dirlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_dirlightsource *dirlightsrc, const t_fragment *fragment)
{
	const t_vec4 to_light = normalize(to_dirlightsource(dirlightsrc));
	const t_rcolor diffcolor = diffuse(lightsrc, fragment, to_light);
	const t_rcolor speccolor = specular(lightsrc, fragment, to_light);
	return (color_add(diffcolor, speccolor));
}

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
	return (-dirlightsrc->direction);
}

t_bool	dirlightsource_is_in_shadow(void)
{
	return (TRUE);
}

t_rcolor	dirlightsource_illuminate(const t_scene *scene, __constant t_lightsource *lightsrc,
__constant t_dirlightsource *dirlightsrc, const t_fragment *fragment)
{
	const t_vec4 to_light = to_dirlightsource(dirlightsrc);
	const t_rcolor diffcolor = diffuse(scene, lightsrc, fragment, to_light);
	const t_rcolor speccolor = specular(scene, lightsrc, fragment, to_light);
	return (diffcolor + speccolor);
}

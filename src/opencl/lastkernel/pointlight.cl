/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec3	to_pointlightsource(__constant t_pointlightsource *pointlightsrc,
const t_vec3 *point)
{
	// return ((t_vec3)(0.0, 0.0, 1.0));
	return (pointlightsrc->position - *point);
}

t_bool	pointlightsource_is_in_shadow(const t_vec3 *to_light, float t)
{
	return (t <= length(*to_light));
}

t_color	pointlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_pointlightsource *pointlightsrc, const t_fragment *fragment)
{
	t_vec3 to_light = to_pointlightsource(pointlightsrc, &fragment->point);
	const t_scalar	attenuation = attenuate(pointlightsrc->attenuation, length(to_light));
	to_light = normalize(to_light);
	const t_color diffcolor = diffuse(lightsrc, fragment, to_light);
	const t_color speccolor = specular(lightsrc, fragment, to_light);
	return (color_scalar(color_add(diffcolor, speccolor), attenuation));
}

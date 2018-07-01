/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.cl                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec3	to_spotlightsource(__constant t_spotlightsource *spotlightsource,
const t_vec3 *point)
{
	return (spotlightsource->position - *point);
}

t_bool	spotlightsource_is_in_shadow(__constant t_spotlightsource *spotlightsrc,
const t_vec3 *to_light, float t)
{
	return (t <= length(*to_light)
	&& spotlightsrc->cosangle <= -dot(*to_light, spotlightsrc->direction));
}

t_color	spotlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_spotlightsource *spotlightsrc, const t_fragment *fragment)
{
	t_vec3 to_light = to_spotlightsource(spotlightsrc, &fragment->point);
	if (spotlightsrc->cosangle > -dot(to_light, spotlightsrc->direction))
		return (0);
	const t_scalar	attenuation = attenuate(spotlightsrc->attenuation, length(to_light));
	to_light = normalize(to_light);
	const t_color diffcolor = diffuse(lightsrc, fragment, to_light);
	const t_color speccolor = specular(lightsrc, fragment, to_light);
	return (color_scalar(color_add(diffcolor, speccolor), attenuation));
}

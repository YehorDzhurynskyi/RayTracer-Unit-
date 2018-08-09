/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlightsource.cl                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec4	to_spotlightsource(__constant t_lightsource *lightsource, const t_vec4 *point)
{
__constant t_primitive *primitive = (__constant t_primitive*)lightsource_skip(lightsource);
return (primitive->position - *point);
}

t_bool	spotlightsource_is_in_shadow(__constant t_spotlightsource *spotlightsrc,
const t_vec4 *to_light, t_scalar t)
{
	return (t <= length(*to_light)
	&& spotlightsrc->cosangle <= -dot(normalize(*to_light), spotlightsrc->direction));
}

t_rcolor	spotlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_spotlightsource *spotlightsrc, const t_fragment *fragment)
{
	t_vec4 to_light = to_spotlightsource(lightsrc, &fragment->point);
	if (spotlightsrc->cosangle > -dot(normalize(to_light), spotlightsrc->direction))
		return (0);
	const t_scalar	attenuation = attenuate(spotlightsrc->attenuation, length(to_light));
	to_light = normalize(to_light);
	const t_rcolor diffcolor = diffuse(lightsrc, fragment, to_light);
	const t_rcolor speccolor = specular(lightsrc, fragment, to_light);
	return ((diffcolor + speccolor) * attenuation);
}

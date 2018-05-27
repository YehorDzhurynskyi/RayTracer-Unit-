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

inline t_vec4		spotlight_to(__constant t_spotlight *spotlight,
const t_vec4 *point)
{
	return (spotlight->position - *point);
}

inline t_bool		spotlight_in_shadow(__constant t_spotlight *spotlight,
const t_vec4 *to_light, float t)
{
	return (t <= length(*to_light)
	&& spotlight->cosangle <= -dot(*to_light, spotlight->direction));
}

uchar4				spotlight_illuminate(__constant t_light *light,
__constant t_spotlight *spotlight, const t_fragment *fragment)
{
	const t_vec4 to_light = normalize(spotlight_to(spotlight, &fragment->point));
	if (spotlight->cosangle > -dot(to_light, spotlight->direction))
		return (0);
	const float	attenuation = attenuate(spotlight->attenuation, length(fragment->to_eye));
	const uchar4 diffcolor = diffuse(light, fragment, to_light);
	const uchar4 speccolor = specular(light, fragment, to_light);
	return (color_scalar(color_add(diffcolor, speccolor), attenuation));
}

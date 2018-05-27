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

inline t_vec4		pointlight_to(__constant t_pointlight *pointlight,
const t_vec4 *point)
{
	return (pointlight->position - *point);
}

inline t_bool		pointlight_in_shadow(const t_vec4 *to_light, float t)
{
	return (t <= length(*to_light));
}

uchar4				pointlight_illuminate(__constant t_light *light,
__constant t_pointlight *pointlight, const t_fragment *fragment)
{
	const t_vec4 to_light = normalize(pointlight_to(pointlight, &fragment->point));
	const float	attenuation = attenuate(pointlight->attenuation, length(fragment->to_eye));
	const uchar4 diffcolor = diffuse(light, fragment, to_light);
	const uchar4 speccolor = specular(light, fragment, to_light);
	return (color_scalar(color_add(diffcolor, speccolor), attenuation));
}

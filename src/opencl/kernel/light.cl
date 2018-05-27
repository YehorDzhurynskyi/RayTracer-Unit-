/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

uchar4			diffuse(__constant t_light *light, const t_fragment *fragment, const t_vec4 to_light)
{
	float ldotn = dot(to_light, fragment->normal);
	if (ldotn <= 0.0)
		return (0);
	const uchar4 diffuse = color_mult(fragment->color, light->color);
	return (color_scalar(diffuse, ldotn * light->intensity));
}

uchar4			specular(__constant t_light *light, const t_fragment *fragment, const t_vec4 to_light)
{
	const t_vec4 from_light = to_light * -1.0f;
	t_vec4	reflected = reflected_vec(from_light, fragment->normal);
	float	specfactor = dot(normalize(fragment->to_eye), reflected);
	specfactor = specfactor <= 0.0 ? 0.0 : specfactor;
	// specfactor = frag->glossiness * pow(specfactor, frag->shininess);
	specfactor = 0.8f * pow(specfactor, 20);
	const uchar4 specular = color_mult(fragment->color, light->color);
	return (color_scalar(specular, specfactor * light->intensity));
}

inline float	attenuate(t_vec4 attenuation, float distance)
{
	return (1.0 / (
	attenuation.x
	+ attenuation.y * distance
	+ attenuation.z * distance * distance));
}
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

t_color		diffuse(__constant t_lightsource *lightsrc,
const t_fragment *fragment, const t_vec4 to_light)
{
	t_scalar ldotn = dot(to_light, fragment->normal);
	if (ldotn <= 0.0)
		return (0);
	const t_color diffuse = color_mult(fragment->color, lightsrc->color);
	return (color_scalar(diffuse, ldotn * lightsrc->intensity));
}

t_color		specular(__constant t_lightsource *lightsrc,
const t_fragment *fragment, const t_vec4 to_light)
{
	const t_vec4 from_light = to_light * -1.0f;
	t_vec4	reflected = reflect3(from_light, fragment->normal);
	t_scalar	specfactor = dot(fragment->to_eye, reflected);
	specfactor = max(0.0f, specfactor);
	specfactor = fragment->glossiness * pow(specfactor, fragment->specularity);
	// if fragment is metal then formula is:
	// const t_color specular = color_mult(lightsrc->color, fragment->color);
	const t_color specular = lightsrc->color;
	return (color_scalar(specular, specfactor * lightsrc->intensity));
}

t_scalar	attenuate(t_vec4 attenuation, t_scalar distance)
{
	return (1.0 / (
	attenuation.x
	+ attenuation.y * distance
	+ attenuation.z * distance * distance));
}

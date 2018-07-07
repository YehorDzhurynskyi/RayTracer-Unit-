/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_scalar	rgb2luma(t_rcolor color)
{
	t_vec3	luma = (t_vec3)(0.299, 0.587, 0.114);
	return ((1.0f - dot(color.xyz, luma)) * 255.0f);
}

t_rcolor			diffuse(__constant t_lightsource *light, const t_fragment *fragment, const t_vec4 to_light)
{
	t_scalar ldotn = dot(to_light, fragment->normal);
	if (ldotn < 0.0f)
		ldotn = 0.0f;
	const t_rcolor diffuse = color_mult(color2rcolor(light->color), fragment->diffuse_albedo);
	return (color_scalar(diffuse, ldotn));
}

t_rcolor			specular(__constant t_lightsource *light, const t_fragment *fragment, const t_vec4 to_light)
{
	const t_vec4 incident = to_light * -1.0f;
	t_vec4	reflected = reflect4(incident, fragment->normal);
	t_scalar	specfactor = dot(normalize(fragment->to_eye), reflected);
	specfactor = max(0.0f, specfactor);
	t_scalar luminosity = rgb2luma(fragment->specular_albedo);
	specfactor = fragment->glossiness * pow(specfactor, luminosity);
	const t_rcolor specular = color_mult(color2rcolor(light->color), fragment->specular_albedo);
	return (color_scalar(specular, specfactor));
}

t_scalar	attenuate(t_vec4 attenuation, t_scalar distance)
{
	return (1.0 / (
	attenuation.x
	+ attenuation.y * distance
	+ attenuation.z * distance * distance));
}

t_vec4		to_lightsource(__constant t_lightsource *lightsrc, const t_vec4 *point)
{
	__constant t_byte *actual = lightsource_get_actual(lightsrc);
	if (lightsrc->lightsource_type == POINTLIGHT)
		return (to_pointlightsource((__constant t_pointlightsource*)actual, point));
	if (lightsrc->lightsource_type == SPOTLIGHT)
		return (to_spotlightsource((__constant t_spotlightsource*)actual, point));
	if (lightsrc->lightsource_type == DIRLIGHT)
		return (to_dirlightsource((__constant t_dirlightsource*)actual));
	return (0);
}

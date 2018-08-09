/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

typedef enum
{
	DIRLIGHT = 1,
	POINTLIGHT,
	SPOTLIGHT
}	t_lightsource_type;

typedef struct			__attribute__ ((packed))
{
	t_address			addr;
	t_color				color;
	t_scalar			intensity;
	t_lightsource_type	lightsource_type;
}	t_lightsource;

typedef struct			__attribute__ ((packed))
{
	t_vec4				direction;
}	t_dirlightsource;

typedef struct			__attribute__ ((packed))
{
	t_vec4				attenuation;
}	t_pointlightsource;

typedef struct			__attribute__ ((packed))
{
	t_vec4				attenuation;
	t_vec4				direction;
	t_scalar			cosangle;
}	t_spotlightsource;

t_vec4					to_lightsource(__constant t_lightsource
*lightsource, const t_vec4 *point);
t_vec4					to_pointlightsource(__constant t_lightsource
*lightsource, const t_vec4 *point);
t_vec4					to_dirlightsource(__constant t_dirlightsource *dirlightsrc);
t_vec4					to_spotlightsource(__constant t_lightsource *lightsource,
const t_vec4 *point);

t_bool					pointlightsource_is_in_shadow(const t_vec4 *to_light, t_scalar t);
t_bool					dirlightsource_is_in_shadow(void);
t_bool					spotlightsource_is_in_shadow(__constant t_spotlightsource *spotlightsrc,
const t_vec4 *to_light, t_scalar t);

t_rcolor				diffuse(__constant t_lightsource *light, const t_fragment *fragment, const t_vec4 to_light);
t_rcolor				specular(__constant t_lightsource *light, const t_fragment *fragment, const t_vec4 to_light);
t_scalar				attenuate(t_vec4 attenuation, t_scalar distance);

#endif

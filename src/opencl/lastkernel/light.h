/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "src/opencl/kernel/common.h"

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
	t_vec3				direction;
}	t_dirlightsource;

typedef struct			__attribute__ ((packed))
{
	t_vec3				position;
	t_vec3				attenuation;
}	t_pointlightsource;

typedef struct			__attribute__ ((packed))
{
	t_vec3				position;
	t_vec3				attenuation;
	t_vec3				direction;
	t_scalar			cosangle;
}	t_spotlightsource;

t_color					pointlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_pointlightsource *pointlightsrc, const t_fragment *fragment);
t_color					dirlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_dirlightsource *dirlightsrc, const t_fragment *fragment);
t_color					spotlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_spotlightsource *spotlightsrc, const t_fragment *fragment);

t_vec3					to_pointlightsource(__constant t_pointlightsource
*pointlightsource, const t_vec3 *point);
t_vec3					to_dirlightsource(__constant t_dirlightsource *dirlightsrc);
t_vec3					to_spotlightsource(__constant t_spotlightsource *spotlightsource,
const t_vec3 *point);

t_bool					pointlightsource_is_in_shadow(const t_vec3 *to_light, float t);
t_bool					dirlightsource_in_shadow(void);
t_bool					spotlightsource_is_in_shadow(__constant t_spotlightsource *spotlightsrc,
const t_vec3 *to_light, float t);

uchar4			diffuse(__constant t_lightsource *light, const t_fragment *fragment, const t_vec3 to_light);
uchar4			specular(__constant t_lightsource *light, const t_fragment *fragment, const t_vec3 to_light);
float	attenuate(t_vec3 attenuation, float distance);

# include "src/opencl/kernel/light.cl"
# include "src/opencl/kernel/pointlight.cl"
# include "src/opencl/kernel/dirlight.cl"
# include "src/opencl/kernel/spotlight.cl"

#endif

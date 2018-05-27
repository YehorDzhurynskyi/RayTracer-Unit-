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
	POINTLIGHT = 1,
	SPOTLIGHT,
	DIRLIGHT
}	t_light_type;

typedef struct		__attribute__ ((packed)) s_light
{
	uchar4			color;
	float			intensity;
	uint			buffer_offset;
	t_light_type	lighttype;
}	t_light;

typedef struct		__attribute__ ((packed)) s_pointlight
{
	t_vec4			position;
	t_vec4			attenuation;
}	t_pointlight;

t_vec4				pointlight_to(__constant t_pointlight *pointlight,
const t_vec4 *point);
uchar4				pointlight_illuminate(__constant t_light *light,
__constant t_pointlight *pointlight, const t_fragment *fragment);
t_bool				pointlight_in_shadow(const t_vec4 *to_light, float t);

typedef struct		__attribute__ ((packed)) s_dirlight
{
	t_vec4			direction;
}	t_dirlight;

t_vec4				dirlight_to(__constant t_dirlight *dirlight);
uchar4				dirlight_illuminate(__constant t_light *light,
__constant t_dirlight *dirlight, const t_fragment *fragment);
t_bool				dirlight_in_shadow(void);

typedef struct		__attribute__ ((packed)) s_spotlight
{
	t_vec4			position;
	t_vec4			attenuation;
	t_vec4			direction;
	float			cosangle;
}	t_spotlight;

t_vec4				spotlight_to(__constant t_spotlight *spotlight,
const t_vec4 *point);
uchar4				spotlight_illuminate(__constant t_light *light,
__constant t_spotlight *spotlight, const t_fragment *fragment);

uchar4				diffuse(__constant t_light *light, const t_fragment *fragment, const t_vec4 to_light);
uchar4				specular(__constant t_light *light, const t_fragment *fragment, const t_vec4 to_light);

# include "src/opencl/kernel/light.cl"
# include "src/opencl/kernel/pointlight.cl"
# include "src/opencl/kernel/dirlight.cl"
# include "src/opencl/kernel/spotlight.cl"

#endif

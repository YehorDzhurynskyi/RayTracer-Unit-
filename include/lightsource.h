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

#ifndef LIGHTSOURCE_H
# define LIGHTSOURCE_H

# include "opencl.h"
# include "ft.h"

typedef enum
{
	DIRLIGHT = 1,
	POINTLIGHT,
	SPOTLIGHT
}	t_lightsource_type;

typedef struct			__attribute__ ((packed))
{
	t_claddress			addr;
	t_clcolor			color;
	t_clscalar			intensity;
	t_lightsource_type	lightsource_type;
}	t_lightsource;

typedef struct			__attribute__ ((packed))
{
	t_clvec4			direction;
}	t_dirlightsource;

typedef struct			__attribute__ ((packed))
{
	t_clvec4			attenuation;
}	t_pointlightsource;

typedef struct			__attribute__ ((packed))
{
	t_clvec4			attenuation;
	t_clvec4			direction;
	t_clscalar			cosangle;
}	t_spotlightsource;

#endif

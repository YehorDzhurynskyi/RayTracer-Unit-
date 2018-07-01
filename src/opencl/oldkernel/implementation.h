/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMPLEMENTATION_H
# define IMPLEMENTATION_H

/*
**	/
*/
# include "color.cl"
// # include "material.cl"
# include "math.cl"

/*
**	/scene
*/
# include "scene/sceneiterator.cl"

/*
**	/shape
*/
# include "shape/cone.cl"
# include "shape/cylinder.cl"
# include "shape/intersection.cl"
// # include "shape/normal.cl"
# include "shape/plane.cl"
# include "shape/shape.cl"
# include "shape/sphere.cl"

/*
**	/lightsource
*/
// # include "lightsource/dirlightsource.cl"
// # include "lightsource/pointlightsource.cl"
// # include "lightsource/spotlightsource.cl"

/*
**	/shading
*/
// # include "shading/shade.cl"
// # include "shading/phong.cl"

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba2vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

inline t_vec3f	rgb2vec3f(unsigned int rgb)
{
	return ((t_vec3f){((rgb >> 16) & 0xff) / 255.0f,
	((rgb >> 8) & 0xff) / 255.0f, ((rgb >> 0) & 0xff) / 255.0f});
}

inline t_vec3d	rgb2vec3d(unsigned int rgb)
{
	return ((t_vec3d){((rgb >> 16) & 0xff) / 255.0,
	((rgb >> 8) & 0xff) / 255.0, ((rgb >> 0) & 0xff) / 255.0});
}

inline t_vec4f	rgba2vec4f(unsigned int rgba)
{
	return ((t_vec4f){((rgba >> 16) & 0xff) / 255.0f,
	((rgba >> 8) & 0xff) / 255.0f, ((rgba >> 0) & 0xff) / 255.0f,
	((rgba >> 24) & 0xff) / 255.0f});
}

inline t_vec4d	rgba2vec4d(unsigned int rgba)
{
	return ((t_vec4d){((rgba >> 16) & 0xff) / 255.0,
	((rgba >> 8) & 0xff) / 255.0, ((rgba >> 0) & 0xff) / 255.0,
	((rgba >> 24) & 0xff) / 255.0});
}

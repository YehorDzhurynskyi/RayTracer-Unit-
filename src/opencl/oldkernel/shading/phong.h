/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_H
# define PHONG_H

t_color		diffuse(__constant t_lightsource *lightsrc,
const t_fragment *fragment, const t_vec4 to_light);
t_color		specular(__constant t_lightsource *lightsrc,
const t_fragment *fragment, const t_vec4 to_light);
t_scalar	attenuate(t_vec4 attenuation, t_scalar distance);

#endif

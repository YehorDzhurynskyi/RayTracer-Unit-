/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILLUMINATION_H
# define ILLUMINATION_H

t_rcolor	illuminate(__constant t_lightsource *lightsource, const t_fragment *fragment);

t_rcolor	pointlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_pointlightsource *pointlightsrc, const t_fragment *fragment);
t_rcolor	dirlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_dirlightsource *dirlightsrc, const t_fragment *fragment);
t_rcolor	spotlightsource_illuminate(__constant t_lightsource *lightsrc,
__constant t_spotlightsource *spotlightsrc, const t_fragment *fragment);

#endif

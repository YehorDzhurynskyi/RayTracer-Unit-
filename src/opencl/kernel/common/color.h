/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

t_rcolor	color2rcolor(const t_color color);
t_color		rcolor2color(t_rcolor color);
t_rcolor	color_mult(const t_rcolor a, const t_rcolor b);
t_rcolor	color_add(const t_rcolor a, const t_rcolor b);
t_rcolor	color_scalar(const t_rcolor color, const t_scalar factor);
t_rcolor	color_mix(const t_rcolor a, const t_rcolor b, const t_scalar factor);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_rcolor	color2rcolor(const t_color color)
{
	t_rcolor rcolor = convert_float4(color);
	return (rcolor / 255.0f);
}

t_color		rcolor2color(t_rcolor color)
{
	color *= 255.0f;
	color.r = min(color.r, 255.0f);
	color.g = min(color.g, 255.0f);
	color.b = min(color.b, 255.0f);
	color.a = min(color.a, 255.0f);
	return (convert_uchar4(color));
}

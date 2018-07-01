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

t_color	color_mult(const t_color a, const t_color b)
{
	t_color result;

	result.r = (a.r / 255.0f) * b.r;
	result.g = (a.g / 255.0f) * b.g;
	result.b = (a.b / 255.0f) * b.b;
	result.a = (a.a / 255.0f) * b.a;
	return (result);
}

t_color	color_add(const t_color a, const t_color b)
{
	t_color result;

	result.r = min(a.r + b.r, 0xff);
	result.g = min(a.g + b.g, 0xff);
	result.b = min(a.b + b.b, 0xff);
	result.a = min(a.a + b.a, 0xff);
	return (result);
}

t_color	color_scalar(const t_color color, const t_scalar factor)
{
	t_color result;

	result.r = min((int)(color.r * factor), 0xff);
	result.g = min((int)(color.g * factor), 0xff);
	result.b = min((int)(color.b * factor), 0xff);
	result.a = min((int)(color.a * factor), 0xff);
	return (result);
}

t_color	color_mix(const t_color a, const t_color b, const t_scalar factor)
{
	return (color_add(color_scalar(a, factor), color_scalar(b, 1.0 - factor)));
}

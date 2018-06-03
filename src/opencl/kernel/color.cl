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

inline uchar4	color_mult(const uchar4 a, const uchar4 b)
{
	uchar4 result;

	result.r = (a.r / 255.0f) * b.r;
	result.g = (a.g / 255.0f) * b.g;
	result.b = (a.b / 255.0f) * b.b;
	result.a = (a.a / 255.0f) * b.a;
	return (result);
}

inline uchar4	color_add(const uchar4 a, const uchar4 b)
{
	uchar4 result;

	result.r = min(a.r + b.r, 0xff);
	result.g = min(a.g + b.g, 0xff);
	result.b = min(a.b + b.b, 0xff);
	result.a = min(a.a + b.a, 0xff);
	return (result);
}

inline uchar4	color_scalar(const uchar4 color, const float factor)
{
	uchar4 result;

	result.r = min((int)(color.r * factor), 0xff);
	result.g = min((int)(color.g * factor), 0xff);
	result.b = min((int)(color.b * factor), 0xff);
	result.a = min((int)(color.a * factor), 0xff);
	return (result);
}

inline uchar4	color_mix(const uchar4 a,
const uchar4 b, const float factor)
{
	uchar4	result;
	float rfactor = 1.0f - factor;

	result.r = min((int)(a.r * factor) + (int)(b.r * rfactor), 0xff);
	result.g = min((int)(a.g * factor) + (int)(b.g * rfactor), 0xff);
	result.b = min((int)(a.b * factor) + (int)(b.b * rfactor), 0xff);
	result.a = min((int)(a.a * factor) + (int)(b.a * rfactor), 0xff);
	return (result);
}

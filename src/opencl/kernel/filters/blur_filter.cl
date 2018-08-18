/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur_filter.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef uchar4	t_color;
typedef float4	t_rcolor;

t_rcolor		color2rcolor(const t_color color);
t_color			rcolor2color(t_rcolor color);

t_rcolor		color2rcolor(const t_color color)
{
	t_rcolor rcolor = convert_float4(color);
	return (rcolor / 255.0f);
}

t_color			rcolor2color(t_rcolor color)
{
	color *= 255.0f;
	color.r = min(color.r, 255.0f);
	color.g = min(color.g, 255.0f);
	color.b = min(color.b, 255.0f);
	color.a = min(color.a, 255.0f);
	return (convert_uchar4(color));
}

t_rcolor		blur(const __global t_color *inputbuffer, int x, int y, int width, int height, int2 direction);

t_rcolor		blur(const __global t_color *inputbuffer, int x, int y, int width, int height, int2 direction)
{
	t_rcolor	color = 0.0f;

	int x1 = x - direction.x >= 0 ? x - direction.x : 0;
	int x2 = x + direction.x < width ? x + direction.x : 0;
	int x3 = x - 2 * direction.x >= 0 ? x - 2 * direction.x : 0;
	int x4 = x + 2 * direction.x < width ? x + 2 * direction.x : 0;

	int y1 = y - direction.y >= 0 ? y - direction.y : 0;
	int y2 = y + direction.y < height ? y + direction.y : 0;
	int y3 = y - 2 * direction.y >= 0 ? y - 2 * direction.y : 0;
	int y4 = y + 2 * direction.y < height ? y + 2 * direction.y : 0;

	color += color2rcolor(inputbuffer[x + y * width]) * 0.2270270270f;
	color += color2rcolor(inputbuffer[x1 + y1 * width]) * 0.3162162162f;
	color += color2rcolor(inputbuffer[x2 + y2 * width]) * 0.3162162162f;
	color += color2rcolor(inputbuffer[x3 + y3 * width]) * 0.0702702703f;
	color += color2rcolor(inputbuffer[x4 + y4 * width]) * 0.0702702703f;

	return (color); 
}

__kernel void	filter(
	__global t_color	*inputbuffer,
	__global t_color	*outputbuffer
)
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	const int width = get_global_size(0);
	const int height = get_global_size(1);

	inputbuffer[x + y * width] = rcolor2color(blur(inputbuffer, x, y, width, height, (int2)(2, 0)));
	outputbuffer[x + y * width] = rcolor2color(blur(inputbuffer, x, y, width, height, (int2)(0, 2)));
}

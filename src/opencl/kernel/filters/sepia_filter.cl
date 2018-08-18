/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepia_filter.cl                                    :+:      :+:    :+:   */
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

__kernel void	filter(
	const __global uchar4 *inputbuffer,
	__global uchar4 *outputbuffer
)
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	const int width = get_global_size(0);

	t_rcolor in = color2rcolor(inputbuffer[x + y * width]);
	in.a = 0.0f;
	in.r = dot(in, float4(0.393f, 0.769f, 0.189f, 0.0f));
	in.g = dot(in, float4(0.349f, 0.686f, 0.168f, 0.0f));
	in.b = dot(in, float4(0.272f, 0.534f, 0.131f, 0.0f));
	outputbuffer[x + y * width] = rcolor2color(in);
}

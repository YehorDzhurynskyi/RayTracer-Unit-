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

static inline float4	get_pixel(const __global uchar4 *inputbuffer, int x, int y, int width)
{
	float4 in = convert_float4_rtz(inputbuffer[x + y * width]);
	return (in / 255.0f);
}

__kernel void		filter(
	const __global uchar4 *inputbuffer,
	__global uchar4 *outputbuffer
)
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	const int width = get_global_size(0);
	const int height = get_global_size(1);


	float4 color = 0;
	float2 off1 = float2(1.411764705882353, 0.0f);
	float2 off2 = float2(3.2941176470588234, 0.0f);
	float2 off3 = float2(5.176470588235294, 0.0f);
	color += get_pixel(inputbuffer, x, y, width) * 0.1964825501511404;
	color += in * 0.1964825501511404;
	color += in * 0.1964825501511404;
	color += in * 0.1964825501511404;
	const uchar4 out = color * 0xff;
	outputbuffer[x + y * width] = out;
}

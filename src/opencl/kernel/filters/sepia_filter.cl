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

__kernel void		filter(
	__global uchar4 *inputbuffer,
	__global uchar4 *outputbuffer
)
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	const int width = get_global_size(0);

	float4 in = convert_float4_rtz(inputbuffer[x + y * width]);
	in /= 255.0f;
	uchar4 out;
	out.r = 0xff * dot(in, float4(0.393f, 0.769f, 0.189f, 0.0f));
	out.g = 0xff * dot(in, float4(0.349f, 0.686f, 0.168f, 0.0f));
	out.b = 0xff * dot(in, float4(0.272f, 0.534f, 0.131f, 0.0f));
	out.a = 0;
	outputbuffer[x + y * width] = out;
}

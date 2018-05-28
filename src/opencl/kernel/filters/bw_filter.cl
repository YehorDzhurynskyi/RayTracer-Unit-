/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_filter.cl                                       :+:      :+:    :+:   */
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

	const uchar4 in = inputbuffer[x + y * width];
	outputbuffer[x + y * width] = max(in.r, max(in.g, in.b));
}

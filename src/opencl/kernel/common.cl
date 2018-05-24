/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef int	t_bool;

#define TRUE 1
#define FALSE 0

typedef struct s_ray	t_ray;
struct		s_ray
{
	float4	origin;
	float4	direction;
};

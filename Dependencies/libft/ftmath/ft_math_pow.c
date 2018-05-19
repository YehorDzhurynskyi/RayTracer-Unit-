/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_pow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:35:58 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:19:05 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int		ft_powi(int i, int n)
{
	if (n <= 0)
		return (1);
	return (i * ft_powi(i, --n));
}

float	ft_powf(float f, int n)
{
	if (n <= 0)
		return (1);
	return (f * ft_powf(f, --n));
}

double	ft_powd(double d, int n)
{
	if (n <= 0)
		return (1);
	return (d * ft_powd(d, --n));
}

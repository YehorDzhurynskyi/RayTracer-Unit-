/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:30:46 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/13 13:33:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.h"

t_complex	complex_sub(const t_complex *z1, const t_complex *z2)
{
	return ((t_complex){z1->re - z2->re, z1->im - z2->im});
}

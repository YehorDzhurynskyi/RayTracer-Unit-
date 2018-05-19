/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:42:37 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/14 14:00:29 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		mini(int *arr, size_t size)
{
	unsigned int	i;
	int				min;

	min = *arr;
	i = 1;
	while (i < size)
	{
		if (min > *arr)
			min = *arr;
		arr++;
		i++;
	}
	return (min);
}

float	minf(float *arr, size_t size)
{
	unsigned int	i;
	float			min;

	min = *arr;
	i = 1;
	while (i < size)
	{
		if (min > *arr)
			min = *arr;
		arr++;
		i++;
	}
	return (min);
}

float	minf_filter(float *arr, size_t size,
		t_bool (*filter)(float v, unsigned int idx))
{
	unsigned int	i;
	float			min;
	t_bool			selected;

	selected = FALSE;
	i = 0;
	min = 0;
	while (i < size)
	{
		if (filter(*arr, i))
		{
			if (!selected)
			{
				selected = TRUE;
				min = *arr;
			}
			else if (min > *arr)
				min = *arr;
		}
		arr++;
		i++;
	}
	return (min);
}

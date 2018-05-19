/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:45:02 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/14 14:00:38 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		maxi(int *arr, size_t size)
{
	unsigned int	i;
	int				max;

	max = *arr;
	i = 1;
	while (i < size)
	{
		if (max < *arr)
			max = *arr;
		arr++;
		i++;
	}
	return (max);
}

float	maxf(float *arr, size_t size)
{
	unsigned int	i;
	float			max;

	max = *arr;
	i = 1;
	while (i < size)
	{
		if (max < *arr)
			max = *arr;
		arr++;
		i++;
	}
	return (max);
}

float	maxf_filter(float *arr, size_t size,
		t_bool (*filter)(float v, unsigned int idx))
{
	unsigned int	i;
	float			max;
	t_bool			selected;

	selected = FALSE;
	i = 0;
	max = 0;
	while (i < size)
	{
		if (filter(*arr, i))
		{
			if (!selected)
			{
				selected = TRUE;
				max = *arr;
			}
			else if (max < *arr)
				max = *arr;
		}
		arr++;
		i++;
	}
	return (max);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:19:09 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/11 15:05:38 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

void		ft_insertion_sort(void *arr, size_t size,
		size_t item_size, const t_comparator_batch *comparators)
{
	unsigned		i;
	unsigned		j;
	t_sort_subject	sbj;

	sbj = (t_sort_subject){arr, size, item_size, comparators};
	i = 0;
	while (++i < size)
	{
		j = i;
		while (j > 0 && sort_compare(&sbj, j, j - 1) < 0)
		{
			sort_swap(&sbj, j, j - 1);
			j--;
		}
	}
}

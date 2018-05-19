/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 16:40:08 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/11 15:07:02 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"

static void	sort(t_sort_subject *sbj, int llim, int rlim)
{
	int		pivot;
	int		i;
	int		j;

	if (llim >= rlim)
		return ;
	pivot = llim;
	i = llim;
	j = rlim + 1;
	while (TRUE)
	{
		while (sort_compare(sbj, pivot, ++i) > 0)
			if (i == rlim)
				break ;
		while (sort_compare(sbj, pivot, --j) < 0)
			if (j == llim)
				break ;
		if (i >= j)
			break ;
		sort_swap(sbj, i, j);
	}
	sort_swap(sbj, llim, j);
	sort(sbj, llim, j - 1);
	sort(sbj, j + 1, rlim);
}

void		ft_quick_sort(void *arr, size_t size,
size_t item_size, const t_comparator_batch *comparators)
{
	t_sort_subject	subject;

	subject = (t_sort_subject){arr, size, item_size, comparators};
	sort(&subject, 0, size - 1);
}

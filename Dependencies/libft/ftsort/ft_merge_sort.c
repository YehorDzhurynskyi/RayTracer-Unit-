/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:13:40 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/12 18:20:03 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"
#include "libft.h"

static void	insert(void *dst, int dst_off, t_sort_subject *sbj, int sbj_off)
{
	ft_memcpy(dst + dst_off * sbj->item_size,
	sbj->arr + sbj_off * sbj->item_size, sbj->item_size);
}

static int	check_overflow(int i_off, int mid, int j_off, int rlim)
{
	if (i_off > mid)
		return (1);
	else if (j_off > rlim)
		return (-1);
	return (0);
}

static void	sort(t_sort_subject *sbj, int llim, int rlim, void *arr)
{
	int	i;
	int	j;
	int	mid;
	int	cmp;
	int	k;

	if (llim == rlim)
		return ;
	mid = (rlim - llim) / 2 + llim;
	sort(sbj, llim, mid, arr);
	sort(sbj, mid + 1, rlim, arr);
	i = 0;
	j = 0;
	k = 0;
	while (i + j < rlim - llim + 1)
	{
		if ((cmp = check_overflow(llim + i, mid, mid + 1 + j, rlim)) == 0)
			cmp = sort_compare(sbj, llim + i, mid + 1 + j);
		if (cmp <= 0)
			insert(arr, llim + k++, sbj, llim + i++);
		else if (cmp > 0)
			insert(arr, llim + k++, sbj, mid + 1 + j++);
	}
	ft_memcpy(sbj->arr + llim * sbj->item_size,
	arr + llim * sbj->item_size, (rlim - llim + 1) * sbj->item_size);
}

void		ft_merge_sort(void *arr, size_t size,
size_t item_size, const t_comparator_batch *comparators)
{
	t_sort_subject	sbj;
	void			*cparr;

	if (!size)
		return ;
	cparr = ft_memalloc(size * item_size);
	if (!cparr)
		return ;
	ft_memcpy(cparr, arr, size * item_size);
	sbj = (t_sort_subject){cparr, size, item_size, comparators};
	sort(&sbj, 0, size - 1, arr);
	ft_memdel((void **)&cparr);
}

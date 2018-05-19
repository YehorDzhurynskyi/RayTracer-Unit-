/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:13:40 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/11 14:43:41 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"
#include "libft.h"

int		sort_compare(t_sort_subject *subject, unsigned int a, unsigned int b)
{
	int			res;
	unsigned	i;
	unsigned	size;
	void		*pa;
	void		*pb;

	pa = subject->arr + a * subject->item_size;
	pb = subject->arr + b * subject->item_size;
	size = subject->comparators->size;
	i = 0;
	res = 0;
	while (i < size && !res)
		res = subject->comparators->comparators[i++](pa, pb);
	return (res);
}

void	sort_swap(t_sort_subject *subject, unsigned int a, unsigned int b)
{
	void	*pa;
	void	*pb;
	void	*temp;

	pa = subject->arr + a * subject->item_size;
	pb = subject->arr + b * subject->item_size;
	temp = ft_memalloc(subject->item_size);
	if (!temp)
		return ;
	ft_memcpy(temp, pa, subject->item_size);
	ft_memcpy(pa, pb, subject->item_size);
	ft_memcpy(pb, temp, subject->item_size);
	ft_memdel((void **)&temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:13:40 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/11 14:43:41 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

# include "libft.h"

typedef int						(*t_comparator)(void *, void*);

struct							s_comparator_batch
{
	t_comparator				*comparators;
	size_t						size;
};

typedef struct s_comparator_batch	t_comparator_batch;

struct							s_sort_subject
{
	void						*arr;
	size_t						size;
	size_t						item_size;
	const t_comparator_batch	*comparators;
};

typedef struct s_sort_subject	t_sort_subject;

void							ft_quick_sort(void *arr, size_t size,
		size_t item_size, const t_comparator_batch *comparators);
void							ft_insertion_sort(void *arr, size_t size,
		size_t item_size, const t_comparator_batch *comparators);
void							ft_merge_sort(void *arr, size_t size,
		size_t item_size, const t_comparator_batch *comparators);

int								sort_compare(t_sort_subject *subject,
		unsigned int a, unsigned int b);
void							sort_swap(t_sort_subject *subject,
		unsigned int a, unsigned int b);

#endif

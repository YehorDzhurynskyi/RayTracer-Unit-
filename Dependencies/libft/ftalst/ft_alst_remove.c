/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alst_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:17:19 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 13:50:05 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alst.h"

t_bool		alst_remove(t_alst *alst, void (*clear)(void **item),
		unsigned int i)
{
	void	**arr;
	int		p;

	if (alst->size == 0)
		return (FALSE);
	arr = alst->array + i;
	if (clear)
		clear(arr);
	p = 0;
	while (i < alst->size - 1)
	{
		*(arr + p) = *(arr + p + 1);
		i++;
		p++;
	}
	alst->size--;
	return (TRUE);
}

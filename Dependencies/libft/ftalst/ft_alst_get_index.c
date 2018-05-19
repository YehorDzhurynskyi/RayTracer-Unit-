/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alst_get_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:24:25 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 13:39:23 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alst.h"

int	alst_get_index(t_alst *alst, void *content, t_bool (*eq)(void*, void*))
{
	unsigned	i;
	void		*item;

	i = 0;
	while (i < alst->size)
	{
		item = alst_get(alst, i);
		if (eq(item, content))
			return (i);
		i++;
	}
	return (-1);
}

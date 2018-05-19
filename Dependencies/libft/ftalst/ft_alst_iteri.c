/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alst_iteri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:10:04 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:10:15 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alst.h"

void		alst_iteri(t_alst *alst, void (*f)(void *content, unsigned int i))
{
	unsigned int i;

	i = 0;
	while (i < alst->size)
	{
		f(alst_get(alst, i), i);
		i++;
	}
}

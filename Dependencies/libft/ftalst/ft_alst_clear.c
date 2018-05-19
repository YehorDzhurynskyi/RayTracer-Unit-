/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alst_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:48:33 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 13:37:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alst.h"

void		alst_clear(t_alst *alst, void (*clear)(void **))
{
	int	i;

	i = alst->size - 1;
	while (i >= 0)
	{
		alst_remove(alst, clear, i);
		i--;
	}
}

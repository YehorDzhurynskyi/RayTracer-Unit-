/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alst_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:07:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:17:08 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alst.h"
#include <stdlib.h>
#include "libft.h"

t_alst		*alst_create(size_t capacity)
{
	t_alst	*alst;

	alst = (t_alst *)malloc(sizeof(t_alst));
	if (!alst)
		return (NULL);
	alst->capacity = capacity;
	alst->size = 0;
	alst->array = (void **)malloc(sizeof(void *) * capacity);
	if (!(alst->array))
	{
		free(alst);
		return (NULL);
	}
	ft_memset(alst->array, 0, sizeof(void *) * capacity);
	return (alst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alst_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>
#include "ft_alst.h"
#include "libft.h"

static void	ensure_capacity(t_alst *alst)
{
	void	**new_array;
	size_t	new_capacity;

	if (alst->size / (float)alst->capacity < 0.85)
		return ;
	new_capacity = alst->capacity + ft_ceil(alst->capacity / 2.0f);
	new_array = (void **)malloc(sizeof(void *) * new_capacity);
	if (!new_array)
		return ;
	ft_memcpy(new_array, alst->array, sizeof(void *) * alst->size);
	free(alst->array);
	alst->array = new_array;
	alst->capacity = new_capacity;
}

void		alst_add(t_alst *alst, void *content)
{
	ensure_capacity(alst);
	*(alst->array + alst->size++) = content;
}

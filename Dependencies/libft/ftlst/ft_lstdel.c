/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:53:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/26 16:02:01 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *t;

	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		t = (*alst)->next;
		free(*alst);
		*alst = t;
	}
	*alst = NULL;
}

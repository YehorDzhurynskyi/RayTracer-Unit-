/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:36:19 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 16:06:21 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static void	*my_memcpy(void *dst, const void *src, size_t n)
{
	char *cdst;
	char *csrc;

	cdst = (char *)dst;
	csrc = (char *)src;
	while (n--)
		cdst[n] = csrc[n];
	return (dst);
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*cont;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (!content)
	{
		new->content_size = 0;
		new->content = NULL;
	}
	else
	{
		new->content_size = content_size;
		cont = malloc(sizeof(content_size));
		cont = my_memcpy(cont, content, content_size);
		new->content = cont;
	}
	new->next = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 18:06:50 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 13:51:55 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		*my_memcpy(void *dst, const void *src, size_t n)
{
	char *cdst;
	char *csrc;

	cdst = (char *)dst;
	csrc = (char *)src;
	while (n--)
		cdst[n] = csrc[n];
	return (dst);
}

static t_list	*my_lstnew(void const *content, size_t content_size)
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

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *))
{
	t_list	*src;
	t_list	*new;
	t_list	*prev;
	int		is_first;

	if (!lst || !f)
		return (NULL);
	is_first = 1;
	while (lst)
	{
		new = f(lst);
		new = my_lstnew(new->content, new->content_size);
		if (!new)
			return (NULL);
		if (is_first)
		{
			src = new;
			is_first = 0;
		}
		else
			prev->next = new;
		prev = new;
		lst = lst->next;
	}
	return (src);
}

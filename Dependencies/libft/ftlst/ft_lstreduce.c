/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreduce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 19:42:03 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/30 14:06:22 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_lstreduce(t_list *lst, void *(*f)(const void *, const void *))
{
	void	*reduce;

	if (!lst || !f)
		return (NULL);
	reduce = lst->content;
	lst = lst->next;
	while (lst)
	{
		reduce = f(reduce, lst->content);
		lst = lst->next;
	}
	return (reduce);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:19:47 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:20:08 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "libft.h"

void		stack_cleanup(t_stack **stack, void (*clear)(void **item))
{
	t_stack *head;
	t_stack *next;

	head = *stack;
	while (head)
	{
		next = head->next;
		if (clear)
			clear((void**)&head->content);
		ft_memdel((void**)&head);
		head = next;
	}
	*stack = NULL;
}

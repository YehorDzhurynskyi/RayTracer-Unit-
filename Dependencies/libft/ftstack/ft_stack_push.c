/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:20:18 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:20:32 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

void	stack_push(t_stack **stack, void *content)
{
	t_stack *new_stack;

	new_stack = stack_create(content);
	if (!new_stack)
		return ;
	new_stack->next = *stack;
	*stack = new_stack;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:20:45 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:20:55 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

void	*stack_pop(t_stack **stack)
{
	void	*content;

	content = (*stack)->content;
	*stack = (*stack)->next;
	return (content);
}

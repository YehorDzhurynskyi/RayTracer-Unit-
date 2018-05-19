/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:42:06 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:21:30 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

# include <string.h>

typedef struct		s_stack
{
	struct s_stack	*next;
	void			*content;
}					t_stack;

t_stack				*stack_create(void *content);
void				stack_push(t_stack **stack, void *content);
void				*stack_pop(t_stack **stack);
void				stack_cleanup(t_stack **stack, void (*clear)(void **item));

#endif

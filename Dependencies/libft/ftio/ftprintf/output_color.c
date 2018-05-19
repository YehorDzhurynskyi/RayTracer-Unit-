/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/02/12 11:37:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include <unistd.h>
#include "libft.h"

#define FT_COLORID_RED     0
#define FT_COLORID_GREEN   1
#define FT_COLORID_YELLOW  2
#define FT_COLORID_BLUE    3
#define FT_COLORID_MAGENTA 4
#define FT_COLORID_CYAN    5
#define FT_COLORID_RESET   6

#define FT_COLOR_RED     "\x1b[31m"
#define FT_COLOR_GREEN   "\x1b[32m"
#define FT_COLOR_YELLOW  "\x1b[33m"
#define FT_COLOR_BLUE    "\x1b[34m"
#define FT_COLOR_MAGENTA "\x1b[35m"
#define FT_COLOR_CYAN    "\x1b[36m"
#define FT_COLOR_RESET   "\x1b[0m"

t_stack		*g_ftcolor_stack = NULL;

void		set_color(int id)
{
	char	*color;

	if (id == 0)
		color = FT_COLOR_RED;
	else if (id == 1)
		color = FT_COLOR_GREEN;
	else if (id == 2)
		color = FT_COLOR_YELLOW;
	else if (id == 3)
		color = FT_COLOR_BLUE;
	else if (id == 4)
		color = FT_COLOR_MAGENTA;
	else if (id == 5)
		color = FT_COLOR_CYAN;
	else
		color = FT_COLOR_RESET;
	write(1, color, ft_strlen(color));
}

static void	push_color(int id)
{
	t_stack	*next;

	next = g_ftcolor_stack;
	g_ftcolor_stack = stack_create((void*)(long long)id);
	if (!g_ftcolor_stack)
		return ;
	g_ftcolor_stack->next = next;
	set_color(id);
}

static void	pop_color(void)
{
	t_stack	*next;
	int		id;

	id = FT_COLORID_RESET;
	if (!g_ftcolor_stack)
		return ;
	next = g_ftcolor_stack->next;
	ft_memdel((void**)&g_ftcolor_stack);
	g_ftcolor_stack = next;
	if (g_ftcolor_stack)
		id = (int)(long long)((void*)g_ftcolor_stack->content);
	set_color(id);
}

t_bool		parse_color(const char *format)
{
	if (ft_strnequ(format, "red}", 4))
		push_color(FT_COLORID_RED);
	else if (ft_strnequ(format, "green}", 6))
		push_color(FT_COLORID_GREEN);
	else if (ft_strnequ(format, "yellow}", 7))
		push_color(FT_COLORID_YELLOW);
	else if (ft_strnequ(format, "blue}", 5))
		push_color(FT_COLORID_BLUE);
	else if (ft_strnequ(format, "magenta}", 8))
		push_color(FT_COLORID_MAGENTA);
	else if (ft_strnequ(format, "cyan}", 5))
		push_color(FT_COLORID_CYAN);
	else if (ft_strnequ(format, "eoc}", 4))
		pop_color();
	else
		return (FALSE);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdarg.h>
#include "recognizer.h"
#include "conversion_handler.h"
#include "output.h"
#include "libft.h"
#include "ft_stack.h"
#include "output_color.h"
#include <unistd.h>

extern t_stack	*g_ftcolor_stack;
int				g_ftprintf_length;
int				g_ftprintf_fd;
va_list			g_ftprintf_srcargs;
va_list			g_ftprintf_args;

int				ft_printf_fd(int fd, const char *format, ...)
{
	unsigned int	n;
	t_bool			valid;

	valid = TRUE;
	n = count_args(format);
	g_ftprintf_length = 0;
	g_ftprintf_fd = fd;
	va_start(g_ftprintf_args, format);
	va_copy(g_ftprintf_srcargs, g_ftprintf_args);
	while (n--)
	{
		process_arg(&format);
		if (g_ftprintf_length < 0)
		{
			valid = FALSE;
			break ;
		}
	}
	shutdown(format, valid);
	return (g_ftprintf_length);
}

int				ft_printf(const char *format, ...)
{
	unsigned int	n;
	t_bool			valid;

	valid = TRUE;
	n = count_args(format);
	g_ftprintf_length = 0;
	g_ftprintf_fd = STDOUT_FILENO;
	va_start(g_ftprintf_args, format);
	va_copy(g_ftprintf_srcargs, g_ftprintf_args);
	while (n--)
	{
		process_arg(&format);
		if (g_ftprintf_length < 0)
		{
			valid = FALSE;
			break ;
		}
	}
	shutdown(format, valid);
	return (g_ftprintf_length);
}

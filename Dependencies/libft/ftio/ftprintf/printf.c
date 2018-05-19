/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "recognizer.h"
#include "conversion_handler.h"
#include "output.h"
#include "libft.h"
#include "ft_stack.h"
#include "output_color.h"
#include <unistd.h>

extern t_stack	*g_ftcolor_stack;
extern va_list	g_ftprintf_srcargs;
extern va_list	g_ftprintf_args;

unsigned int	count_args(const char *format)
{
	unsigned int	n;

	n = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			while (is_flag(*format) || *format == '.' ||
			*format == '$' || *format == '*' ||
			is_length_modifier(*format) || ft_isdigit(*format))
				format++;
			if (ft_isalpha(*format) || *format == '%')
				n++;
			if (!*format)
				return (n);
		}
		format++;
	}
	return (n);
}

void			print_plain_text(const char *format, size_t size)
{
	while (size--)
	{
		if (*format == '{' && parse_color(format + 1))
		{
			while (*format != '}')
			{
				format++;
				size--;
			}
			format++;
			continue ;
		}
		if (*format != '%')
			buff_write(format, 1);
		format++;
	}
}

int				process_arg(const char **format)
{
	char	*option;

	option = ft_strchr(*format, '%');
	if (!option)
		option = ft_strrchr(*format, '\0');
	if (option && option - *format > 0)
		print_plain_text(*format, option - *format);
	if (option)
	{
		*format = option;
		if (!process_conversion(format))
			return (FALSE);
	}
	return (TRUE);
}

void			shutdown(const char *format, t_bool valid)
{
	va_end(g_ftprintf_args);
	va_end(g_ftprintf_srcargs);
	if (valid)
		print_plain_text(format, ft_strlen(format));
	if (g_ftcolor_stack)
	{
		stack_cleanup(&g_ftcolor_stack, NULL);
		set_color(6);
	}
}

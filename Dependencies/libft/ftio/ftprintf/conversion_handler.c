/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion_handler.h"
#include "conversion.h"
#include "text_manager.h"
#include "number_manager.h"
#include <float.h>
#include <stdarg.h>

extern int			g_ftprintf_length;
extern va_list		g_ftprintf_args;

static void			process_integer(t_conversion *c)
{
	if (c->type >= type_d && c->type <= type_X
	&& c->length_mode == lm_h)
		print_hinteger(c);
	else if (c->type >= type_d && c->type <= type_X
	&& c->length_mode == lm_hh)
		print_hhinteger(c);
	else if ((c->type >= type_d && c->type <= type_X
	&& c->length_mode == lm_l) || (c->type >= type_D && c->type <= type_U))
		print_linteger(c);
	else if ((c->type >= type_d && c->type <= type_X
	&& c->length_mode == lm_ll) || c->type == type_p)
		print_llinteger(c);
	else if (c->type >= type_d && c->type <= type_X
	&& c->length_mode == lm_z)
		print_zinteger(c);
	else if (c->type >= type_d && c->type <= type_X
	&& c->length_mode == lm_j)
		print_jinteger(c);
	else if (c->type >= type_d && c->type <= type_X
	&& c->length_mode == lm_ptrdiff)
		print_tinteger(c);
	else if (c->type >= type_d && c->type <= type_X)
		print_integer(c);
}

static void			process_text(t_conversion *c)
{
	char			*str;
	unsigned int	l;

	if ((c->type == type_s && c->length_mode == lm_l) || c->type == type_S)
		print_wstr(c, (wchar_t *)va_arg(g_ftprintf_args, wchar_t *));
	else if (c->type == type_s)
	{
		str = (char *)va_arg(g_ftprintf_args, char *);
		l = 0;
		if (str)
			l = ft_strlen(str);
		print_str(c, str, l);
	}
	else if ((c->type == type_c && c->length_mode == lm_l) || c->type == type_C)
		print_wchar(c, (wchar_t)va_arg(g_ftprintf_args, wint_t));
	else if (c->type == type_c)
		print_char(c, (unsigned char)va_arg(g_ftprintf_args, int));
	else if (c->type == type_percent)
		print_char(c, '%');
}

static void			override_flags(t_conversion *c)
{
	if (c->field_width < 0)
	{
		c->minus_flag = TRUE;
		c->field_width = -c->field_width;
	}
	if (c->precision < 0 && c->type >= type_d && c->type <= type_U)
		c->precision = -c->precision < (int)c->field_width
		&& c->zero_flag && !c->minus_flag ? -c->precision : -1;
	if (c->plus_flag)
		c->space_flag = 0;
	if (c->minus_flag)
		c->zero_flag = 0;
	if (c->precision < 0 && (c->type == type_s || c->type == type_S))
		c->precision = -1;
	if (c->precision == 0 && (c->type == type_g || c->type == type_G))
		c->precision = 1;
	if (!c->dot_present)
	{
		if (c->type >= type_p && c->type <= type_U)
			c->precision = -1;
		else if (c->type == type_S || c->type == type_s)
			c->precision = -1;
		else if (c->type >= type_f && c->type <= type_E)
			c->precision = 6;
	}
}

int					process_conversion(const char **format)
{
	t_conversion	c;
	int				*n;

	c = get_conversion(*format + 1);
	*format += c.shift;
	if (!c.type && c.field_width)
		print_char(&c, *(*format)++);
	if (!c.is_valid)
		return (FALSE);
	override_flags(&c);
	if (c.type >= type_percent && c.type <= type_S)
		process_text(&c);
	else if (c.type >= type_p && c.type <= type_U)
		process_integer(&c);
	else if (c.type >= type_f && c.type <= type_E)
		print_real(&c);
	else if (c.type == type_n)
	{
		n = (int *)va_arg(g_ftprintf_args, int *);
		*n = g_ftprintf_length;
	}
	return (TRUE);
}

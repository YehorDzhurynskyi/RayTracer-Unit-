/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "recognizer.h"
#include "libft.h"

void		set_value(const char **format,
t_conversion *c, t_option *option)
{
	if (option->variable)
		*option->variable = option->value;
	c->shift += option->shift;
	*format += option->shift;
}

int			parse_conversion(const char **format, t_conversion *c)
{
	t_type		type;
	t_option	o;

	type = recognize_type(**format);
	o = (t_option){(int *)&c->type, (int)type, 1};
	if (!type)
	{
		c->is_valid = FALSE;
		return (FALSE);
	}
	set_value(format, c, &o);
	return (TRUE);
}

void		parse_num(int *variable, int val,
const char **format, t_conversion *c)
{
	t_option		o;
	unsigned int	size;

	o = (t_option){variable, val, 0};
	size = 0;
	if (val == 0)
		size = 1;
	else
	{
		if (val < 0)
			size++;
		while (val)
		{
			size++;
			val /= 10;
		}
	}
	o.shift = size;
	set_value(format, c, &o);
}

void		parse_flag(const char **format, t_conversion *c)
{
	t_option	o;

	o = (t_option){NULL, TRUE, 1};
	if (**format == '0' && !c->dot_present)
		o.variable = &c->zero_flag;
	else if (**format == '-')
		o.variable = &c->minus_flag;
	else if (**format == '+')
		o.variable = &c->plus_flag;
	else if (**format == '#')
		o.variable = &c->hash_flag;
	else if (**format == ' ')
		o.variable = &c->space_flag;
	else if (**format == '\'')
		o.variable = &c->apostrophe_flag;
	set_value(format, c, &o);
}

void		parse_length_modifier(char ch,
const char **format, t_conversion *c)
{
	t_option	o;

	o = (t_option){NULL, 0, 1};
	if (!c->length_mode
	|| (c->length_mode == lm_l && ch == 'l')
	|| (c->length_mode == lm_h && ch == 'h'))
	{
		if (ch == 'z')
			o.value = lm_z;
		else if (ch == 'j')
			o.value = lm_j;
		else if (ch == 'L')
			o.value = lm_upper_l;
		else if (ch == 't')
			o.value = lm_ptrdiff;
		else if (ch == 'l')
			o.value = c->length_mode == lm_l ? lm_ll : lm_l;
		else if (ch == 'h')
			o.value = c->length_mode == lm_h ? lm_hh : lm_h;
		o.variable = (int *)&c->length_mode;
	}
	set_value(format, c, &o);
}

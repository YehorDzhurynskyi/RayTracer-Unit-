/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "parser.h"

extern va_list	g_ftprintf_args;
extern va_list	g_ftprintf_srcargs;

void			seti_arg(int i)
{
	va_list	item;

	if (i <= 0)
		return ;
	va_copy(item, g_ftprintf_srcargs);
	while (--i >= 1)
		va_arg(item, void*);
	va_copy(g_ftprintf_args, item);
	va_end(item);
}

t_bool			is_wildcard(const char *str)
{
	while (ft_isdigit(*str) || *str == '-' || *str == '+')
		str++;
	return (*str == '$');
}

int				parse_placeholder(t_conversion *c, const char **f)
{
	int		res;

	res = ft_atoi(*f);
	if (res < 0)
		res = 0;
	while (**f != '$')
	{
		(*f)++;
		c->shift++;
	}
	(*f)++;
	c->shift++;
	return (res);
}

void			parse_wildcard(t_conversion *c, const char **f)
{
	t_option	o;
	t_bool		is_wc;
	const char	*ff;

	ff = *f + 1;
	o = (t_option){NULL, 0, 0};
	is_wc = is_wildcard(ff);
	if (is_wc)
		seti_arg(ft_atoi(ff));
	o.value = (int)va_arg(g_ftprintf_args, int);
	if (!c->dot_present)
		o.variable = (int *)&c->field_width;
	else if (c->dot_present)
		o.variable = &c->precision;
	o.shift += is_wc ? ft_strchr(*f, '$') - *f + 1 : 1;
	set_value(f, c, &o);
}

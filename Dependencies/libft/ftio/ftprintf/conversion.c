/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "libft.h"
#include "recognizer.h"
#include "parser.h"
#include "wildcard.h"

static void		process_dot(const char **f, t_conversion *c)
{
	c->dot_present = TRUE;
	c->shift++;
	(*f)++;
}

static t_bool	get_special(t_conversion *c, const char **f)
{
	if (is_flag(**f))
		parse_flag(f, c);
	else if (is_length_modifier(**f))
		parse_length_modifier(**f, f, c);
	else if (**f == '.')
		process_dot(f, c);
	else
		return (FALSE);
	return (TRUE);
}

static t_bool	get_numeric(t_conversion *c, const char **f)
{
	if (**f == '*')
		parse_wildcard(c, f);
	else if (ft_isdigit(**f) && !c->dot_present)
		parse_num((int *)&c->field_width, ft_atoi(*f), f, c);
	else if (ft_isdigit(**f) && c->dot_present)
		parse_num((int *)&c->precision, ft_atoi(*f), f, c);
	else
		return (FALSE);
	return (TRUE);
}

t_conversion	get_conversion(const char *f)
{
	t_conversion	c;
	int				argi;

	c = (t_conversion){0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0};
	argi = 0;
	if (ft_isdigit(*f) && is_wildcard(f))
		argi = parse_placeholder(&c, &f);
	while (*f && !c.type)
	{
		if ((ft_isalpha(*f) && !is_length_modifier(*f)) || *f == '%')
		{
			if (!parse_conversion(&f, &c))
				return (c);
		}
		else if (!get_special(&c, &f) && !get_numeric(&c, &f))
		{
			c.is_valid = FALSE;
			return (c);
		}
	}
	seti_arg(argi);
	return (c);
}

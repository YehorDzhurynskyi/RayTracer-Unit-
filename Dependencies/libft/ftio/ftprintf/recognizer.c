/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "recognizer.h"

static t_type	recognize_integer_type(char ch)
{
	if (ch == 'd')
		return (type_d);
	else if (ch == 'D')
		return (type_D);
	else if (ch == 'i')
		return (type_i);
	else if (ch == 'b')
		return (type_b);
	else if (ch == 'o')
		return (type_o);
	else if (ch == 'O')
		return (type_O);
	else if (ch == 'u')
		return (type_u);
	else if (ch == 'U')
		return (type_U);
	else if (ch == 'x')
		return (type_x);
	else if (ch == 'X')
		return (type_X);
	return (0);
}

static t_type	recognize_real_type(char ch)
{
	if (ch == 'f')
		return (type_f);
	else if (ch == 'F')
		return (type_F);
	else if (ch == 'e')
		return (type_e);
	else if (ch == 'E')
		return (type_E);
	else if (ch == 'g')
		return (type_g);
	else if (ch == 'G')
		return (type_G);
	return (0);
}

t_type			recognize_type(char ch)
{
	t_type	t;

	if ((t = recognize_integer_type(ch)) != 0)
		return (t);
	else if ((t = recognize_real_type(ch)) != 0)
		return (t);
	else if (ch == '%')
		return (type_percent);
	else if (ch == 'n')
		return (type_n);
	else if (ch == 's')
		return (type_s);
	else if (ch == 'S')
		return (type_S);
	else if (ch == 'p')
		return (type_p);
	else if (ch == 'c')
		return (type_c);
	else if (ch == 'C')
		return (type_C);
	return (0);
}

int				is_flag(char ch)
{
	return (ch == '0' || ch == '+'
	|| ch == '-' || ch == '#' || ch == ' ' || ch == '\'');
}

int				is_length_modifier(char ch)
{
	return (ch == 'l' || ch == 'h' || ch == 'z'
	|| ch == 'j' || ch == 'L' || ch == 't');
}

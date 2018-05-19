/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "number_manager.h"
#include "real_manager.h"
#include "recognizer.h"
#include "libft.h"
#include "conversion.h"
#include "output.h"
#include "recognizer.h"

char		g_nbuff[NBSIZE];
extern char	g_fracbuff[];
const char	g_upper_alphabet[] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const char	g_lower_alphabet[] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char		*get_prefix(int is_negative, const t_conversion *c, const char *num)
{
	if (c->type == type_d || c->type == type_D || c->type == type_i
	|| is_real_conversion(c->type))
	{
		if (is_negative)
			return ("-");
		else if (c->plus_flag)
			return ("+");
		else if (c->space_flag)
			return (" ");
	}
	else if ((c->type == type_o || c->type == type_O)
	&& (*num != '0' || !c->precision) && c->hash_flag)
		return ("0");
	else if (c->type == type_p
	|| (c->type == type_x && *num != '0' && c->hash_flag))
		return ("0x");
	else if (c->type == type_X && *num != '0' && c->hash_flag)
		return ("0X");
	return ("");
}

unsigned	get_base(const t_conversion *c)
{
	if (c->type == type_b)
		return (2);
	else if (c->type == type_o || c->type == type_O)
		return (8);
	else if (c->type == type_x || c->type == type_X || c->type == type_p)
		return (16);
	return (10);
}

static void	print_major_part(size_t fracsize,
const t_nument *ent, const t_conversion *c)
{
	unsigned	i;

	i = 0;
	while (i++ < ent->size - ent->int_len
	- ent->prefix_len - fracsize - ent->suffix_len)
		buff_write((char[]){'0'}, 1);
	buff_write(g_nbuff, ent->int_len);
	if (is_real_conversion(c->type))
	{
		if (dot_present(ent->frac_len, c))
			buff_write((char[]){'.'}, 1);
		buff_write(g_fracbuff, ent->frac_len);
		i = 0;
		if (c->precision > (int)ent->frac_len
		&& c->type != type_g && c->type != type_G)
			while (i++ < c->precision - ent->frac_len)
				buff_write((char[]){'0'}, 1);
	}
}

void		print_nument(const char *prefix,
const char *suffix, const t_nument *ent, const t_conversion *c)
{
	size_t	fracsize;

	fracsize = 0;
	if (is_real_conversion(c->type))
		fracsize = dot_present(ent->frac_len, c) + ent->frac_len;
	if (!c->minus_flag)
		print_filler(c, ent->size);
	buff_write(prefix, ent->prefix_len);
	print_major_part(fracsize, ent, c);
	buff_write(suffix, ent->suffix_len);
	if (c->minus_flag)
		print_filler(c, ent->size);
}

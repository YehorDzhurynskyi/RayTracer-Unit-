/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "number_manager.h"
#include "output.h"

extern char			g_nbuff[];
extern char			g_fracbuff[];
extern const char	g_upper_alphabet[];
extern const char	g_lower_alphabet[];
extern va_list		g_ftprintf_args;

size_t				fill_integer(char *dest,
unsigned long long n, const t_conversion *c)
{
	size_t		num_len;
	unsigned	base;
	unsigned	i;
	int			thousands_sep;

	base = get_base(c);
	num_len = ft_count_num_length(n, base);
	thousands_sep = c->apostrophe_flag ? (num_len - 1) / 3 : 0;
	num_len += thousands_sep;
	i = 0;
	while (i++ < num_len)
	{
		if (thousands_sep && i % 4 == 0)
		{
			dest[num_len - i] = ',';
			continue ;
		}
		if (c->type == type_X)
			dest[num_len - i] = g_upper_alphabet[n % base];
		else
			dest[num_len - i] = g_lower_alphabet[n % base];
		n /= base;
	}
	return (num_len);
}

static size_t		get_size(t_conversion *c, const t_nument *ent)
{
	size_t	size;

	size = ent->prefix_len + ent->int_len;
	if (c->zero_flag || c->precision != -1)
	{
		if (c->precision == -1 && c->field_width > (int)size)
			size = c->field_width;
		else
		{
			if (c->precision < (int)c->field_width)
				c->zero_flag = FALSE;
			size = ent->prefix_len
			+ (c->precision > (int)ent->int_len ? c->precision : ent->int_len);
			if (c->hash_flag && c->precision > (int)ent->int_len &&
			(c->type == type_o || c->type == type_O) && *g_nbuff != '0')
				size--;
		}
	}
	return (size);
}

void				print_inumber(unsigned long long n,
int is_negative, t_conversion *c)
{
	t_nument	ent;
	char		*prefix;

	ent = (t_nument){0, 0, 0, 0, 0};
	ent.int_len = fill_integer(g_nbuff, n, c);
	prefix = get_prefix(is_negative, c, g_nbuff);
	ent.prefix_len = ft_strlen(prefix);
	if (c->precision == 0 && *g_nbuff == '0')
	{
		c->zero_flag = FALSE;
		print(c, prefix, ent.prefix_len);
		return ;
	}
	ent.size = get_size(c, &ent);
	print_nument(prefix, "", &ent, c);
}

void				print_integer(t_conversion *c)
{
	unsigned long long	n;
	int					is_neg;

	is_neg = 0;
	if (c->type == type_d || c->type == type_i)
	{
		n = (int)va_arg(g_ftprintf_args, int);
		if ((int)n < 0)
		{
			is_neg = 1;
			n = ~n + 1;
		}
	}
	else
		n = (unsigned int)va_arg(g_ftprintf_args, unsigned int);
	print_inumber(n, is_neg, c);
}

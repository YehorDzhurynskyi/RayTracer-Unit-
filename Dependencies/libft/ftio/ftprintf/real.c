/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "number_manager.h"
#include "real_manager.h"
#include "ft_float.h"

extern char		g_nbuff[];
char			g_fracbuff[FBSIZE + 1];
extern va_list	g_ftprintf_args;

t_bool			dot_present(size_t frac_len, const t_conversion *c)
{
	if (c->type == type_g || c->type == type_G)
		return (frac_len > 0 || c->hash_flag);
	else
		return (c->precision > 0 || c->hash_flag);
}

static size_t	get_size(const t_nument *ent, const t_conversion *c)
{
	size_t	size;

	size = ent->prefix_len + ent->int_len
	+ ent->frac_len + dot_present(ent->frac_len, c) + ent->suffix_len;
	if (c->zero_flag && (int)size < c->field_width)
		size = c->field_width;
	return (size);
}

static char		*get_suffix(const t_conversion *c, const t_nument *ent, int ex)
{
	static char		suffix[32];
	int				i;

	if (c->type == type_e || c->type == type_E
	|| c->type == type_g || c->type == type_G)
	{
		suffix[0] = c->type == type_e || c->type == type_g ? 'e' : 'E';
		suffix[1] = ex < 0 ? '-' : '+';
		if (ex < 0)
			ex = -ex;
		i = 0;
		while (i < (int)ent->suffix_len - 2)
		{
			suffix[ent->suffix_len - 1 - i++] = ex % 10 + '0';
			ex /= 10;
		}
		return (suffix);
	}
	return ("");
}

void			print_lrnumber(long double n, t_conversion *c)
{
	int			precision;
	t_nument	ent;
	t_bool		is_neg;
	int			ex;
	char		*prefix;

	is_neg = is_ldneg(n);
	precision = c->precision;
	ex = 0;
	if (c->precision > FBSIZE)
		c->precision = FBSIZE;
	if (c->type == type_f || c->type == type_F)
		ent = get_flreal(n, c);
	else if (c->type == type_e || c->type == type_E)
		ent = get_elreal(n, c, &ex);
	else if (c->type == type_g || c->type == type_G)
		ent = get_glreal(n, c, &ex);
	else
		ent = get_flreal(n, c);
	c->precision = precision;
	prefix = get_prefix(is_neg, c, g_nbuff);
	ent.prefix_len = ft_strlen(prefix);
	ent.size = get_size(&ent, c);
	print_nument(prefix, get_suffix(c, &ent, ex), &ent, c);
}

void			print_real(t_conversion *c)
{
	long double	ld;
	t_bool		small;

	small = c->type >= type_f && c->type <= type_e;
	if (c->length_mode == lm_upper_l)
		ld = (long double)va_arg(g_ftprintf_args, long double);
	else
		ld = (double)va_arg(g_ftprintf_args, double);
	if (is_ldnan(ld))
		print_nan(small, c);
	else if (is_ldinf(ld))
		print_inf(is_ldneg(ld), small, c);
	else
		print_lrnumber(ld, c);
}

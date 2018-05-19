/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greal.c                                            :+:      :+:    :+:   */
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
#include "libft.h"

extern char	g_nbuff[];
extern char	g_fracbuff[];

static void	trail_zeroes(t_nument *ent,
const t_conversion *c, t_bool is_exp_format)
{
	int	i;

	if (c->hash_flag && !is_exp_format)
		return ;
	i = ent->frac_len;
	while (--i > 0)
	{
		if (g_fracbuff[i] != '0')
		{
			ent->frac_len -= ent->frac_len - i;
			return ;
		}
	}
	ent->frac_len = 0;
}

t_nument	get_glreal(long double n, t_conversion *c, int *ex)
{
	t_nument	ent;
	t_bool		is_exp_format;

	is_exp_format = TRUE;
	ent = get_elreal(n, c, ex);
	if (*ex >= -4 && *ex < c->precision)
	{
		is_exp_format = FALSE;
		ent = get_flreal(n, c);
	}
	trail_zeroes(&ent, c, is_exp_format);
	return (ent);
}

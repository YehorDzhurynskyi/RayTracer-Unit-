/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ereal.c                                            :+:      :+:    :+:   */
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

extern char			g_nbuff[];
extern char			g_fracbuff[];

static int			get_expon(long double n)
{
	int	ex;

	ex = 0;
	n = is_ldneg(n) ? -n : n;
	if (n > 0.0l && n < 1.0l)
	{
		while ((unsigned long long)n == 0)
		{
			n *= 10.0l;
			ex--;
		}
	}
	else
	{
		while ((unsigned long long)n >= 10)
		{
			n /= 10.0l;
			ex++;
		}
	}
	return (ex);
}

static long double	get_normalized(long double n)
{
	t_bool	is_neg;

	is_neg = is_ldneg(n);
	n = is_neg ? -n : n;
	if (n > 0.0l && n < 1.0l)
	{
		while ((unsigned long long)n == 0)
			n *= 10.0l;
	}
	else
	{
		while ((unsigned long long)n >= 10)
			n /= 10.0l;
	}
	return (is_neg ? -n : n);
}

static t_bool		check(int *ex, long double *n, size_t int_len)
{
	unsigned	i;

	if (int_len != 1)
	{
		*ex += *ex < 0 ? -(int_len - 1) : int_len - 1;
		i = 0;
		while (i < int_len - 1)
		{
			*n /= 10.0l;
			i++;
		}
		return (FALSE);
	}
	return (TRUE);
}

t_nument			get_elreal(long double n, t_conversion *c, int *ex)
{
	t_nument	ent;

	ent = (t_nument){0, 0, 0, 0, 0};
	*ex = get_expon(n);
	n = get_normalized(n);
	while (TRUE)
	{
		ent = get_flreal(n, c);
		if (check(ex, &n, ent.int_len))
			break ;
	}
	ent.suffix_len = *ex < 0 ?
	ft_count_num_length(-(*ex), 10) : ft_count_num_length(*ex, 10);
	ent.suffix_len = ent.suffix_len <= 2 ? 4 : ent.suffix_len + 2;
	return (ent);
}

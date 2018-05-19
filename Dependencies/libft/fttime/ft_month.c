/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_month.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:13:40 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/11 14:43:41 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "libft.h"

static const char	g_months[12][3] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

t_month				get_month_from_ctime(const char *ctime_str)
{
	t_month	i;

	i = -1;
	while (i < 12)
	{
		if (ft_strnequ(g_months[++i], ctime_str + 4, 3))
			return (i);
	}
	return (-1);
}

t_month				get_month_diff(t_year ya, t_month ma, t_year yb, t_month mb)
{
	t_month	res;

	res = get_year_diff(ya, yb) * 12 + ma - mb;
	return (res < 0 ? -res : res);
}

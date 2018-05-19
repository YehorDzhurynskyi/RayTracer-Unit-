/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_year.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:13:40 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/11 14:43:41 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "libft.h"

t_year	get_year_from_ctime(const char *ctime_str)
{
	return (ft_atoi(ft_strrchr(ctime_str, ' ') + 1));
}

t_year	get_year_diff(t_year a, t_year b)
{
	t_year	res;

	res = a - b;
	return (res < 0 ? -res : res);
}

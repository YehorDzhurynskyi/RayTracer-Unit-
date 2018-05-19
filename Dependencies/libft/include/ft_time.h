/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:13:40 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/11 14:43:41 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

typedef int	t_month;
typedef int	t_year;

t_month	get_month_from_ctime(const char *ctime_str);
t_month	get_month_diff(t_year ya, t_month ma, t_year yb, t_month mb);
t_year	get_year_from_ctime(const char *ctime_str);
t_year	get_year_diff(t_year a, t_year b);

#endif

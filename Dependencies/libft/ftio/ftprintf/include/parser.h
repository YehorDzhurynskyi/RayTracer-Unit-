/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "conversion.h"

void		parse_num(int *variable, int val,
const char **format, t_conversion *c);
void		parse_flag(const char **format, t_conversion *c);
int			parse_conversion(const char **format, t_conversion *c);
void		parse_length_modifier(char ch,
const char **format, t_conversion *c);
void		set_value(const char **format,
t_conversion *c, t_option *option);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECOGNIZER_H
# define RECOGNIZER_H

# include "conversion.h"

t_type	recognize_type(char ch);
int		is_flag(char ch);
int		is_length_modifier(char ch);
t_bool	is_real_conversion(t_type type);
t_bool	is_int_conversion(t_type type);

#endif

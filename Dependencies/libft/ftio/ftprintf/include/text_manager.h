/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_manager.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_MANAGER_H
# define TEXT_MANAGER_H

# include "conversion.h"
# include <wchar.h>

void	print_str(t_conversion *c, const char *src, unsigned int size);
void	print_char(t_conversion *c, unsigned char ch);
void	print_address(t_conversion *c, void const *pointer);
void	print_wstr(t_conversion *c, const wchar_t *src);
void	print_wchar(t_conversion *c, wchar_t ch);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_logger.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

void	cson_log_parsing_error(t_cson_parser *parser,
const char *msg, char error_symbol, int errcode)
{
	*parser->err = errcode;
	ft_printf_fd(2, "[%#x] CSON Parsing error (on line: %d)"
	" on symbol - '%c' (ascii code is %d): %s\n",
	errcode, parser->current_line, error_symbol, (int)error_symbol, msg);
}

void	cson_log_error(t_cson_parser *parser, const char *msg, int errcode)
{
	*parser->err = errcode;
	ft_printf_fd(2, "[%#x] CSON Parsing error (on line: %d): %s\n",
	errcode, parser->current_line, msg);
}

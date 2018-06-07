/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSON_PARSER_H
# define CSON_PARSER_H

# include "cson.h"
# include <errno.h>

# define CSON_PARSER_BEFORE_KEY_STATE	0
# define CSON_PARSER_KEY_STATE			1
# define CSON_PARSER_AFTER_KEY_STATE	2
# define CSON_PARSER_BEFORE_VALUE_STATE	3
# define CSON_PARSER_STRING_VALUE_STATE	4
# define CSON_PARSER_NUMBER_VALUE_STATE	5
# define CSON_PARSER_TRUE_VALUE_STATE	6
# define CSON_PARSER_FALSE_VALUE_STATE	7
# define CSON_PARSER_EOV_STATE			8

typedef enum e_handler_status	t_handler_status;
enum				e_handler_status
{
	handler_error,
	handler_skip,
	handler_record
};

typedef struct s_cson_parser	t_cson_parser;
struct				s_cson_parser
{
	t_cson			*root;
	t_cson			*current;
	t_cson			*parent;
	char			*buffer;
	size_t			buffer_size;
	int				buffer_offset;
	int				state;
	int				current_line;
	t_error_code	*err;
	int				array_depth;
	int				bounded_object_depth;
	t_bool			is_comment;
};

void				cson_log_parsing_error(t_cson_parser *parser,
const char *msg, char error_symbol, t_error_code errcode);
void				cson_log_error(t_cson_parser *parser,
const char *msg, t_error_code errcode);

t_bool				cson_parser_init(t_cson_parser *parser, t_error_code *err);
t_cson				*cson_parser_done(t_cson_parser *parser);
void				cson_parser_fail(t_cson_parser *parser);
void				cson_parser_free(t_cson_parser *parser);

void				cson_parse_chunk(t_cson_parser *parser,
const char *buffer, size_t size);
t_bool				cson_assign_value(t_cson_parser *parser);
t_bool				cson_create_node(t_cson_parser *parser);

t_handler_status	cson_compose_object(t_cson_parser *parser);
t_handler_status	cson_compose_array(t_cson_parser *parser);

t_bool				cson_is_key_symbol(char ch);
t_bool				cson_is_quoted_key(const t_cson_parser *parser);
t_handler_status	cson_process_quoted_key(t_cson_parser *parser, char ch);

/*
**	Finite-state machine handlers
*/
typedef t_handler_status	(*t_state_handler)(t_cson_parser *parser, char ch);

t_handler_status	cson_boolean_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_eov_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_before_value_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_after_key_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_key_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_before_key_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_number_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_string_handler(t_cson_parser *parser, char ch);

t_bool				cson_flush_buffer(t_cson_parser *parser);
t_bool				cson_ensure_buffer_capacity(t_cson_parser *parser);

#endif

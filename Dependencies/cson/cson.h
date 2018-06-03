/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSON_H
# define CSON_H

# include "ft.h"

# define CSON_PARSER_BSIZE		4096
# define CSON_PRODUCER_BSIZE	4096

# define CSON_UNDEFINED_VALUE_TYPE	0x0
# define CSON_STRING_VALUE_TYPE		0x1
# define CSON_INTEGER_VALUE_TYPE	0x2
# define CSON_REAL_VALUE_TYPE		0x3
# define CSON_BOOLEAN_VALUE_TYPE	0x4
# define CSON_ARRAY_VALUE_TYPE		0x5
# define CSON_OBJECT_VALUE_TYPE		0x6

# define CSON_MEM_ALLOC_ERROR			0x1
# define CSON_FILE_OPENING_ERROR		0x2
# define CSON_FILE_READING_ERROR		0x3
# define CSON_KEY_PARSING_ERROR			0x4
# define CSON_VALUE_PARSING_ERROR		0x5
# define CSON_BRACKETS_PARSING_ERROR	0x6
# define CSON_EMPTY_DATA_PARSING_ERROR	0x7
# define CSON_NULL_PARAMETER_ERROR		0x8

typedef union u_cson_value	t_cson_value;
union				u_cson_value
{
	long long		integer;
	double			real;
	long long		boolean;
	char			*string;
	t_alst			*tuple;
};

typedef struct s_cson		t_cson;
struct				s_cson
{
	char			*key;
	t_cson_value	value;
	int				value_type;
	t_cson			*parent;
};

typedef int	t_error_code;

/*
**	DEALLOC
*/
void				cson_free(t_cson *cson);

/*
**	PARSING
*/
t_cson				*cson_parse_file(const char *filename, t_error_code *err);
t_cson				*cson_parse_str(const char *str,
size_t size, t_error_code *err);

/*
**	PRODUCING
*/
t_error_code		cson_produce_file(const t_cson *cson,
const char *filename, t_bool override_file);
char				*cson_produce_str(const t_cson *cson,
size_t *size, t_error_code *err);

/*
**	NAVIGATION
*/
t_bool				cson_is_string(const t_cson *cson);
t_bool				cson_is_integer(const t_cson *cson);
t_bool				cson_is_real(const t_cson *cson);
t_bool				cson_is_boolean(const t_cson *cson);
t_bool				cson_is_primitive(const t_cson *cson);
t_bool				cson_is_array(const t_cson *cson);
t_bool				cson_is_object(const t_cson *cson);
t_bool				cson_is_composite(const t_cson *cson);

const char			*cson_get_string(const t_cson *cson);
long long			cson_get_integer(const t_cson *cson);
double				cson_get_real(const t_cson *cson);
t_bool				cson_get_boolean(const t_cson *cson);
const t_alst		*cson_get_array(const t_cson *cson);
const t_alst		*cson_get_object(const t_cson *cson);

const t_cson		*cson_valueof(const t_cson *cson, const char *key);
const t_cson		*cson_at(const t_cson *cson, unsigned int index);
const t_cson		*cson_find(const t_cson *cson, char *nodepath);

/*
**	MISC
*/
void				cson_foreach(const t_cson *cson,
void (*func)(const t_cson *item));
int					cson_depth(const t_cson *cson);
int					cson_size(const t_cson *cson);
void				cson_print(const t_cson *cson);
const t_cson		*cson_root(const t_cson *cson);

#endif

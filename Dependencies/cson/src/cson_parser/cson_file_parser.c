/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_file_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

static t_bool	open_cson_file(const char *filename, t_cson_parser *parser)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		cson_log_error(parser, strerror(errno), CSON_FILE_OPENING_ERROR);
		cson_parser_fail(parser);
	}
	return (fd);
}

t_cson			*cson_parse_file(const char *filename, int *err)
{
	int				fd;
	t_cson_parser	parser;
	char			buffer[CSON_PARSER_BSIZE + 1];
	ssize_t			ret;

	if (cson_parser_init(&parser, err) == FALSE)
		return (NULL);
	if ((fd = open_cson_file(filename, &parser)) < 0)
		return (NULL);
	while ((ret = read(fd, buffer, CSON_PARSER_BSIZE)) > 0)
	{
		cson_parse_chunk(&parser, buffer, (size_t)ret);
		if (*parser.err != 0)
			break ;
	}
	if (ret < 0)
	{
		cson_log_error(&parser, strerror(errno), CSON_FILE_READING_ERROR);
		cson_parser_fail(&parser);
	}
	close(fd);
	return (cson_parser_done(&parser));
}

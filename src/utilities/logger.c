/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"
#include "ft.h"
#include <stdlib.h>

#include "gui.h"

#define LOGBUFFER_SIZE	256

char	log_type[LOGBUFFER_SIZE];
char	*log_buf;

void				log_notify(const char *message)
{
	// TODO: add status console as notification target
	int text_len;

	ft_bzero(log_type, LOGBUFFER_SIZE);
	text_len = ft_strlen(message);
	ft_memcpy(&log_type, "[INFO]\n", 7);
	ft_memcpy(&log_type[7], message, text_len);
	ft_memcpy(&log_type[7 + text_len], "\n", 1);
	ft_printf_fd(2, "{green}[INFO]{eoc} %s\n", message);
	if (!log_buf)
		log_buf = ft_strdup(log_type);
	else
	{
		char *buff = ft_strdup(log_buf);
		ft_strdel(&log_buf);
		log_buf = ft_strjoin(log_type, buff);
		ft_strdel(&buff);
		ft_printf("--> %d\n", ft_strlen(log_buf));
	}
}

static const char	*get_error_message(t_err_code code)
{
	if (code == RT_UNDEFINED_ERROR)
		return ("undefined error");
	else if (code == RT_NO_ERROR)
		return ("no error");
	else if (code == RT_FILE_OPENING_ERROR)
		return ("file opening error");
	else if (code == RT_MEM_ALLOC_ERROR)
		return ("memory allocation error");
	else if (code == RT_FILE_READING_ERROR)
		return ("file reading error");
	else if (code == RT_KEY_PARSING_ERROR)
		return ("CSON key parsing error");
	else if (code == RT_VALUE_PARSING_ERROR)
		return ("CSON value parsing error");
	else if (code == RT_BRACKETS_PARSING_ERROR)
		return ("CSON brackets parsing error");
	else if (code == RT_EMPTY_DATA_PARSING_ERROR)
		return ("CSON empty data parsing error");
	else if (code == RT_NULL_PARAMETER_ERROR)
		return ("null parameter error");
	else if (code == RT_WRONG_VALUE_FORMAT_ERROR)
		return ("wrong value format error");
	else if (code == RT_WRONG_DIMENSION_ERROR)
		return ("wrong value dimension error");
	else if (code == RT_NO_REQUIRED_VALUE_ERROR)
		return ("required value is absent error");
	else if (code == RT_ZERO_LENGTH_VECTOR_ERROR)
		return ("zero length vector error");
	else if (code == RT_COMMAND_LINE_PARSING_ERROR)
		return ("command line argument's parsing error");
	else if (code == RT_SDL_ERROR)
		return ("SDL error");
	else if (code == RT_OPENCL_ERROR)
		return ("OPENCL error");
	else if (code == RT_BUFFER_OVERFLOW_ERROR)
		return ("buffer overflow error");
	return (NULL);
}

static void			log_violation(const char *level,
const char *message, t_err_code code)
{
	// int level_len;
	// int text_len;
	
	// level_len = ft_strlen(level);
	
	ft_printf_fd(2, "{red}[%s - %s]{eoc}: %s\n", level, get_error_message(code), message);
	
	// ft_bzero(log_type, LOGBUFFER_SIZE);
	// text_len = ft_strlen(message);
	// ft_memcpy(&log_type, level_len, 7);
	// ft_memcpy(&log_type[7], message, text_len);
	// ft_memcpy(&log_type[7 + text_len], "\n", 1);
	// ft_printf_fd(2, "{green}[INFO]{eoc} %s\n", message);
	// if (!log_buf)
	// 	log_buf = ft_strdup(log_type);
	// else
	// {
	// 	char *buff = ft_strdup(log_buf);
	// 	ft_strdel(&log_buf);
	// 	log_buf = ft_strjoin(log_type, buff);
	// 	ft_strdel(&buff);
	// 	ft_printf("--> %d\n", ft_strlen(log_buf));
	// }
}

void				log_error(const char *message, t_err_code code)
{
	// TODO: add status console as notification target
	// add special behavior for opencl error and maybe SDL
	log_violation("ERROR", message, code);
}

void				log_fatal(const char *message, t_err_code code)
{
	log_violation("FATAL ERROR", message, code);
	exit(EXIT_FAILURE);
}

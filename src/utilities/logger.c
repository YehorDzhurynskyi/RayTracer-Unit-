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
#include "window.h"
#include "gui.h"

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
	else if (code == RT_RESOURCE_LOADING_ERROR)
		return ("resource loading error");
	else if (code == RT_WRONG_VALUE_RANGE_ERROR)
		return ("value range error");
	else if (code == RT_WRONG_VALUE_TYPE_ERROR)
		return ("wrong type error");
	return (NULL);
}

void				log_notify(const char *message)
{
	gui_info_log_notify(message);
}

void				log_error(const char *message, t_err_code code)
{
	gui_info_log_error(message, get_error_message(code));
	ft_printf_fd(2, "{red}[ERROR - %s]{eoc}: %s\n", get_error_message(code), message);
	if (code == RT_OPENCL_ERROR)
		window_warning(RT_APP_NAME " OpenCL error", message);
	else if (code == RT_SDL_ERROR)
		window_warning(RT_APP_NAME " SDL error", message);
}

void				log_fatal(const char *message, t_err_code code)
{
	ft_printf_fd(2, "{red}[FATAL ERROR - %s]{eoc}: %s\n", get_error_message(code), message);
	exit(EXIT_FAILURE);
}

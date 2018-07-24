/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# define STRINGIFY(x)	#x
# define TO_STRING(x)	STRINGIFY(x)

# define RT_USAGE "usage: RT [-w frame_width] [-h frame_height] [scene_name]"

typedef int	t_err_code;

# define RT_UNDEFINED_ERROR				-1
# define RT_NO_ERROR					0
# define RT_FILE_OPENING_ERROR			2
# define RT_MEM_ALLOC_ERROR				3
# define RT_FILE_READING_ERROR			4
# define RT_KEY_PARSING_ERROR			5
# define RT_VALUE_PARSING_ERROR			6
# define RT_BRACKETS_PARSING_ERROR		7
# define RT_EMPTY_DATA_PARSING_ERROR	8
# define RT_NULL_PARAMETER_ERROR		9
# define RT_WRONG_VALUE_FORMAT_ERROR	10
# define RT_WRONG_DIMENSION_ERROR		11
# define RT_NO_REQUIRED_VALUE_ERROR		12
# define RT_ZERO_LENGTH_VECTOR_ERROR	13
# define RT_COMMAND_LINE_PARSING_ERROR	14
# define RT_SDL_ERROR					15
# define RT_OPENCL_ERROR				16
# define RT_BUFFER_OVERFLOW_ERROR		17
# define RT_WRONG_VALUE_TYPE_ERROR		18
# define RT_RESOURCE_LOADING_ERROR		19
# define RT_WRONG_VALUE_RANGE_ERROR		20

void	log_notify(const char *message);
void	log_error(const char *message, t_err_code code);
void	log_fatal(const char *message, t_err_code code);

#endif

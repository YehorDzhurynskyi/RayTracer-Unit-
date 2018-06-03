/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_producer_logger.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_producer.h"

void	cson_log_producing_error(const char *msg, int errcode)
{
	ft_printf_fd(2, "[%#x] CSON Producing error: %s\n", errcode, msg);
}

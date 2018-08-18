/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# define QUEUE_MAX_SIZE	10

typedef struct
{
	t_ray		ray;
	t_scalar	intensity;
}	t_queue_elem;

typedef struct
{
	t_queue_elem	data[QUEUE_MAX_SIZE];
	int				begin;
	int				end;
}	t_queue;

t_queue	queue_init(void);
t_bool	queue_pop(t_queue *queue, t_queue_elem *elem);
t_bool	queue_push(t_queue *queue, t_queue_elem *elem);

#endif

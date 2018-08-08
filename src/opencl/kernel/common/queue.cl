/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_bool	queue_pop(t_queue *queue, t_queue_elem *elem)
{
	const int	size = queue->end % QUEUE_MAX_SIZE - queue->begin % QUEUE_MAX_SIZE + 1;
	if (size > 0) 
	{
		*elem = queue->data[queue->begin++ % QUEUE_MAX_SIZE];
		return (TRUE);
	}
	return (FALSE);
}

t_bool	queue_push(t_queue *queue, t_queue_elem *elem)
{
	const int	size = queue->end % QUEUE_MAX_SIZE - queue->begin % QUEUE_MAX_SIZE + 1;
	if (size < QUEUE_MAX_SIZE) 
	{
		queue->data[++queue->end % QUEUE_MAX_SIZE] = *elem;
		return (TRUE);
	}
	return (FALSE);
}

t_queue	queue_init(void)
{
	t_queue	queue;

	queue.begin = 0;
	queue.end = -1;
	return (queue);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 19:20:25 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/29 19:26:08 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"

int	request_dongle(t_coder *coder, t_dongle *dongle)
{
	t_request	req;

	req.coder_id = coder->id;
	req.deadline = coder->last_compile_start + coder->config->time_to_burnout;
	req.timestamp = get_time_ms() - coder->config->start_time;
	pthread_mutex_lock(&dongle->scheduler.mutex);
	if (!heap_push(&dongle->scheduler.pending, req, coder->config->scheduler))
	{
		pthread_mutex_unlock(&dongle->scheduler.mutex);
		return (0);
	}
	while (dongle->taken
		|| heap_peek(&dongle->scheduler.pending).coder_id != coder->id
		|| (get_time_ms()
			- dongle->last_released_at) < coder->config->dongle_cooldown)
	{
		pthread_cond_wait(&dongle->scheduler.cond, &dongle->scheduler.mutex);
	}
	heap_pop(&dongle->scheduler.pending, coder->config->scheduler);
	dongle->taken = 1;
	pthread_mutex_unlock(&dongle->scheduler.mutex);
	return (1);
}

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->scheduler.mutex);
	dongle->taken = 0;
	dongle->last_released_at = get_time_ms();
	pthread_cond_broadcast(&dongle->scheduler.cond);
	pthread_mutex_unlock(&dongle->scheduler.mutex);
}

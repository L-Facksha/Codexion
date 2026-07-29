/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 21:17:28 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/29 22:31:47 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"
#include <stdlib.h>

static int	init_resources(t_dongle *dongles, int i, int count)
{
	dongles[i].id = i;
	dongles[i].taken = 0;
	dongles[i].last_released_at = 0;
	dongles[i].scheduler.pending.capacity = count;
	dongles[i].scheduler.pending.size = 0;
	dongles[i].scheduler.pending.data = malloc(sizeof(t_request) * count);
	if (!dongles[i].scheduler.pending.data)
	{
		cleanup_init_dongle(dongles, i);
		return (0);
	}
	return (1);
}

int	init_dongles(t_dongle *dongles, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!init_resources(dongles, i, count))
			return (0);
		if (pthread_mutex_init(&dongles[i].mutex, NULL) != 0)
			return (fail_mutex(dongles, i));
		if (pthread_mutex_init(&dongles[i].scheduler.mutex, NULL) != 0)
			return (fail_scheduler_mutex(dongles, i));
		if (pthread_cond_init(&dongles[i].scheduler.cond, NULL) != 0)
			return (fail_cond(dongles, i));
		i++;
	}
	return (1);
}

int	init_coders(t_coder *coders, t_dongle *dongles, t_config *config)
{
	int i = 0;

	while (i < config->number_of_coders)
	{
		coders[i].id = i;
		coders[i].left = &dongles[i];
		coders[i].right = &dongles[(i + 1) % config->number_of_coders];
		coders[i].config = config;
		i++;
	}
	return (1);
}
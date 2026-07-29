/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:28:27 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/28 17:39:05 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	int		i;

	t_dongle *first, *second;
	// long timestamp;
	i = 0;
	coder = (t_coder *)arg;
	if (coder->left->id < coder->right->id)
	{
		first = coder->left;
		second = coder->right;
	}
	else
	{
		first = coder->right;
		second = coder->left;
	}
	while (i < coder->config->number_of_compiles_required)
	{
		pthread_mutex_lock(&first->mutex);
		// timestamp = get_time_ms() - coder->config->start_time;
		// printf("%ld %d has taken a dongle\n", timestamp, coder->id);
		print_status(coder, "has taken a dongle");
		pthread_mutex_lock(&second->mutex);
		// timestamp = get_time_ms() - coder->config->start_time;
		// printf("%ld %d has taken a dongle\n", timestamp, coder->id);
		print_status(coder, "has taken a dongle");
		// timestamp = get_time_ms() - coder->config->start_time;
		// printf("%ld %d is compiling\n", timestamp, coder->id);
		print_status(coder, "is compiling");
		usleep(coder->config->time_to_compile * 1000);
		pthread_mutex_unlock(&second->mutex);
		pthread_mutex_unlock(&first->mutex);
		// timestamp = get_time_ms() - coder->config->start_time;
		// printf("%ld %d is debugging\n", timestamp, coder->id);
		print_status(coder, "is debugging");
		usleep(coder->config->time_to_debug * 1000);
		// timestamp = get_time_ms() - coder->config->start_time;
		// printf("%ld %d is refactoring\n\n", timestamp, coder->id);
		print_status(coder, "is refactoring");
		usleep(coder->config->time_to_refactor * 1000);
		i++;
	}
	return (NULL);
}

int	create_threads(t_coder *coders, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		if (pthread_create(&coders[i].thread, NULL, coder_routine,
				&coders[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < config->number_of_coders)
	{
		if (pthread_join(coders[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

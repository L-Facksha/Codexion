/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 22:15:53 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/29 21:58:39 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"

void	cleanup(t_config *config, t_coder *coders, t_dongle *dongels)
{
	pthread_mutex_destroy(&config->print_mutex);
	free(coders);
	free(dongels);
}

void	cleanup_init_dongle(t_dongle *dongle, int count)
{
	int i;
	i = 0;
	while (i < count)
	{
		free(dongle[i].scheduler.pending.data);
		pthread_mutex_destroy(&dongle[i].mutex);
		pthread_mutex_destroy(&dongle[i].scheduler.mutex);
		pthread_cond_destroy(&dongle[i].scheduler.cond);
		i++;
	}
}
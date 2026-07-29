/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_donge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 22:26:30 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/29 22:31:31 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"

int	fail_mutex(t_dongle *dongles, int i)
{
	free(dongles[i].scheduler.pending.data);
	cleanup_init_dongle(dongles, i);
	return (0);
}

int	fail_scheduler_mutex(t_dongle *dongles, int i)
{
	pthread_mutex_destroy(&dongles[i].mutex);
	free(dongles[i].scheduler.pending.data);
	cleanup_init_dongle(dongles, i);
	return (0);
}

int	fail_cond(t_dongle *dongles, int i)
{
	pthread_mutex_destroy(&dongles[i].scheduler.mutex);
	pthread_mutex_destroy(&dongles[i].mutex);
	free(dongles[i].scheduler.pending.data);
	cleanup_init_dongle(dongles, i);
	return (0);
}
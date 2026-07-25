/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 21:17:28 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/25 21:22:36 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"
#include <stdlib.h>

int	init_dongles(t_dongle *dongles, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dongles[i].id = i;
		if (pthread_mutex_init(&dongles[i].mutex, NULL) != 0)
			return (0);
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
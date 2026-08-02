/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:01:45 by azebahad          #+#    #+#             */
/*   Updated: 2026/08/02 19:59:24 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/codixion.h"

void	*monitor_routine(void *arg)
{
	t_runtime	*runtime;
	t_coder		*coders;
	t_config		*config;
	int			i;
	long			now;

	runtime = (t_runtime *)arg;
	coders = runtime->coders;
	config = runtime->config;
	while (!should_stop(config))
	{
		i = 0;
		while (i < config->number_of_coders && !should_stop(config))
		{
			now = get_time_ms() - config->start_time;
			if (!coders[i].burned_out && coders[i].state == STATE_WAITING
				&& coders[i].last_compile_start >= 0
				&& now - coders[i].last_compile_start >= config->time_to_burnout)
			{
				coders[i].burned_out = 1;
				set_coder_state(&coders[i], STATE_BURNED_OUT);
				print_burnout(&coders[i]);
				set_simulation_stop(config, 0);
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

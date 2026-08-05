/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:01:45 by azebahad          #+#    #+#             */
/*   Updated: 2026/08/05 14:01:43 by azebahad         ###   ########.fr       */
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

            /* Read shared fields under state_mutex to avoid data races */
            pthread_mutex_lock(&config->state_mutex);
            int burned_flag = coders[i].burned_out;
            t_state st = coders[i].state;
            long last_start = coders[i].last_compile_start;
            pthread_mutex_unlock(&config->state_mutex);

            if (!burned_flag && st == STATE_WAITING && last_start >= 0
                && now - last_start >= config->time_to_burnout)
            {
                /* set burned_out under lock to avoid races */
                pthread_mutex_lock(&config->state_mutex);
                coders[i].burned_out = 1;
                pthread_mutex_unlock(&config->state_mutex);

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 17:29:39 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/28 18:30:09 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"

void schedulare_waite_turn(t_coder *coder)
{
    t_scheduler *scheduler;

    scheduler = &coder->config->schedulare;

    pthread_mutex_lock(&scheduler->turn_mutex);
    whiel(coder->id != scheduler->next_coder)
    {
        pthread_cond_wait(&scheduler->turn_change, &scheduler->turn_mutex);
    }
    pthread_mutex_unlock(&scheduler->turn_mutex);
}



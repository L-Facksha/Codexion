/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 22:15:53 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/27 22:19:06 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"

void cleanup(t_config *config, t_coder *coders, t_dongle *dongels)
{
    pthread_mutex_destroy(&config->print_mutex);
    free(coders);
    free(dongels);
}
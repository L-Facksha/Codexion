/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 19:44:35 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/27 19:44:36 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
	{
		return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		// printf("Seconds: %ld\n", tv.tv_sec * 1000);
		// printf("Microseconds: %ld\n", tv.tv_usec / 1000);
		// printf("%ld\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	}
	else
	{
		perror("gettimeofday failed");
		return (-1);
	}
}

// int main(){
//     t_config config;
//     config.start_time = get_time_ms();
//     printf("%ld\n", config.start_time);
//     sleep(1);
//     long time = get_time_ms() - config.start_time;
//     printf("%ld\n", time);
//     printf("%ld\n", config.start_time);
//     return (0);
// }
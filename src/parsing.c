/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 21:17:38 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/26 14:55:14 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codixion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	parse_nb(char *nb)
{
	int			i;
	long long	res;

	i = 0;
	if (nb[i] == '+')
		i++;
	while (nb[i])
	{
		if ((nb[i] >= '0' && nb[i] <= '9'))
			i++;
		else
		{
			printf("Error: Invalid number '%c'\n", nb[i]);
			return (-1);
		}
	}
	res = atoi((const char *)nb);
	if (res <= 0)
	{
		printf("Error: Invalid argument foramt\n");
		return (-1);
	}
	return (res);
}

char	*parse_schedulare(char *sch)
{
	if (strcmp(sch, "fifo") == 0)
		return (sch);
	else if (strcmp(sch, "edf") == 0)
		return (sch);
	else
	{
		printf("Error: Last argument must be 'fifo' or 'edf'\n");
		return (NULL);
	}
}

int	parse_args(int ac, char **av, t_config *config)
{
	int		i;
	int		res;
	char	*test_sch;

	if (ac != 9)
		return (-1);
	i = 1;
	while (i < ac - 1)
	{
		res = parse_nb(av[i]);
		if (res == -1)
			return (0);
		i++;
	}
	config->number_of_coders = parse_nb(av[1]);
	config->time_to_burnout = parse_nb(av[2]);
	config->time_to_compile = parse_nb(av[3]);
	config->time_to_debug = parse_nb(av[4]);
	config->time_to_refactor = parse_nb(av[5]);
	config->number_of_compiles_required = parse_nb(av[6]);
	config->dongle_cooldown = parse_nb(av[7]);
	if (!parse_schedulare(av[8]))
		return (0);
	config->scheduler = parse_schedulare(av[8]);
	return (1);
}

// int	main(int ac, char **av)
// {
// 	t_config	config;
// 	int			x;

// 	x = parse_args(ac, av, &config);
// 	if (x == -1)
// 	{
// 		printf("Error: Missing argument!\n");
// 		return (1);
// 	}
// 	if (x == 0)
// 		return (1);
// 	printf("number_of_coders                = %d\n", config.number_of_coders);
// 	printf("time_to_burnout                 = %d\n", config.time_to_burnout);
// 	printf("time_to_compile                 = %d\n", config.time_to_compile);
// 	printf("time_to_debug                   = %d\n", config.time_to_debug);
// 	printf("time_to_refactor                = %d\n", config.time_to_refactor);
// 	printf("number_of_compiles_required     = %d\n",
// 		config.number_of_compiles_required);
// 	printf("dongle_cooldown                 = %d\n", config.dongle_cooldown);
// 	printf("scheduler                       = %s\n", config.scheduler);
// 	return (0);
// }

// int main(int ac, char **av)
// {
//     t_config config;

//     if (parse_args(ac, av, &config) == -1)
//     {
//         printf("Error\n");
//         return (1);
//     }

//     printf("number_of_coders          = %d\n", config.number_of_coders);
//     printf("time_to_burnout           = %ld\n", config.time_to_burnout);
//     printf("time_to_compile           = %ld\n", config.time_to_compile);
//     printf("time_to_debug             = %ld\n", config.time_to_debug);
//     printf("time_to_refactor          = %ld\n", config.time_to_refactor);
//     printf("number_of_compiles_req    = %d\n",
// config.number_of_compiles_required);
//     printf("dongle_cooldown           = %d\n", config.dongle_cooldown);
//     printf("scheduler                 = %s\n", config.scheduler);

//     return (0);
// }
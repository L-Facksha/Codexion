#include "../include/codixion.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_config config;
	t_dongle *dongles = NULL;
	t_coder *coders = NULL;

	int x = parse_args(ac, av, &config);

	if (x != 1)
	{
		if (x == -1)
			printf("Error: Missing argument!\n");
		return (1);
	}

	config.start_time = get_time_ms();

	if (pthread_mutex_init(&config.print_mutex, NULL) != 0)
	{
		printf("Error: mutex initialization failed\n");
		return (1);
	}

	dongles = malloc(sizeof(t_dongle) * config.number_of_coders);
	if (!dongles)
	{
		cleanup(&config, coders, dongles);
		return (1);
	}

	coders = malloc(sizeof(t_coder) * config.number_of_coders);
	if (!coders)
	{
		cleanup(&config, coders, dongles);
		return (1);
	}

	if (!init_dongles(dongles, config.number_of_coders))
	{
		cleanup(&config, coders, dongles);
		return (1);
	}

	if (!init_coders(coders, dongles, &config))
	{
		cleanup(&config, coders, dongles);
		return (1);
	}

	if (!create_threads(coders, &config))
	{
		cleanup(&config, coders, dongles);
		return (1);
	}

	cleanup(&config, coders, dongles);

	return (0);
}
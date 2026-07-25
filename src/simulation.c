#include "../include/codixion.h"
#include <pthread.h>
#include <stdio.h>

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	printf("Coder %d started\n", coder->id);
	return (NULL);
}

int	create_threads(t_coder *coders, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		if (pthread_create(&coders[i].thread, NULL, coder_routine,
				&coders[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < config->number_of_coders)
	{
		if (pthread_join(coders[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

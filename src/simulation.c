#include "../include/codixion.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *coder_routine(void *arg)
{
	t_dongle *first, *second;
	t_coder *coder;
	int i = 0;

	coder = (t_coder *)arg;
	if (coder->left->id < coder->right->id)
	{
		first = coder->left;
		second = coder->right;
	}
	else
	{
		first = coder->right;
		second = coder->left;
	}
	while (i < coder->config->number_of_compiles_required)
	{
		pthread_mutex_lock(&first->mutex);
		printf("Coder %d has taken a dongle\n", coder->id);

		pthread_mutex_lock(&second->mutex);
		printf("Coder %d has taken a dongle\n", coder->id);

		printf("Coder %d is compiling\n", coder->id);
		usleep(coder->config->time_to_compile * 1000);

		pthread_mutex_unlock(&second->mutex);
		pthread_mutex_unlock(&first->mutex);

		printf("Coder %d is debugging\n", coder->id);
		usleep(coder->config->time_to_debug * 1000);
		printf("Coder %d is refactoring\n\n", coder->id);
		usleep(coder->config->time_to_refactor * 1000);

		i++;
	}
	return (NULL);
}

int create_threads(t_coder *coders, t_config *config)
{
	int i;

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

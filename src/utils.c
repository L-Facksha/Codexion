#include "../include/codixion.h"
#include <sys/time.h>

void	print_status(t_coder *coder, const char *status)
{
	pthread_mutex_lock(&coder->config->print_mutex);

	long timestamp;
	timestamp = get_time_ms() - coder->config->start_time;
	printf("%ld %d %s\n", timestamp, coder->id, status);

	pthread_mutex_unlock(&coder->config->print_mutex);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codixion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 21:17:32 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/28 22:37:49 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_request
{
	int coder_id;
	long timestamp;
	long deadline;
} t_request;

typedef struct s_heap
{
	t_request *data;
	int size;
	int capacity;
} t_heap;

typedef struct s_scheduler
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	t_heap *pending;
} t_scheduler;

typedef struct s_config
{
	int number_of_coders;
	int time_to_burnout;
	int time_to_compile;
	int time_to_debug;
	int time_to_refactor;
	int number_of_compiles_required;
	int dongle_cooldown;
	char *scheduler;
	long start_time;
	pthread_mutex_t print_mutex;

} t_config;

typedef struct s_dongle
{
	int id;
	pthread_mutex_t mutex;
	int taken;
	long last_released_at;
	t_scheduler scheduler;

} t_dongle;

typedef struct s_coder
{
	int id;
	pthread_t thread;
	t_dongle *left;
	t_dongle *right;
	t_config *config;
	long	last_compile_start;
	int		compiles_done;

} t_coder;

// todo PARSING:
int parse_args(int ac, char **av, t_config *config);

// todo initialize INITIALIZE CODERS AND DONGLES
int init_dongles(t_dongle *dongles, int count);
int init_coders(t_coder *coders, t_dongle *dongles,
				t_config *config);

// todo SIMULATION
int create_threads(t_coder *coders, t_config *config);

// todo CALCULATE TIME
long get_time_ms(void);

// todo PRINT STATUS
void print_status(t_coder *coder, const char *status);

// todo CLEANUP
void cleanup(t_config *config, t_coder *coders,
			 t_dongle *dongels);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codixion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 21:17:32 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/29 22:31:35 by azebahad         ###   ########.fr       */
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
	int				coder_id;
	long			timestamp;
	long			deadline;
}					t_request;

typedef struct s_heap
{
	t_request		*data;
	int				size;
	int				capacity;
}					t_heap;

typedef struct s_scheduler
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_heap			pending;
}					t_scheduler;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
	int				taken;
	long			last_released_at;
	t_scheduler		scheduler;

}					t_dongle;

typedef struct s_config
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
	long			start_time;
	pthread_mutex_t	print_mutex;

}					t_config;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	t_config		*config;
	long			last_compile_start;
	int				compiles_done;

}					t_coder;

// todo PARSING: (parsing.c)
int					parse_args(int ac, char **av, t_config *config);

// todo initialize INITIALIZE CODERS AND DONGLES (init.c)
int					init_dongles(t_dongle *dongles, int count);
int					init_coders(t_coder *coders, t_dongle *dongles,
						t_config *config);

// todo SIMULATION (simulation.c)
int					create_threads(t_coder *coders, t_config *config);

// todo CALCULATE TIME (timer.c)
long				get_time_ms(void);

// todo PRINT STATUS (utils.c)
void				print_status(t_coder *coder, const char *status);

// todo CLEANUP (cleanup.c)
void				cleanup(t_config *config, t_coder *coders,
						t_dongle *dongels);
void				cleanup_init_dongle(t_dongle *dongle, int count);

// todo FAIL DONGLES (fail_dongle.c)
int					fail_mutex(t_dongle *dongles, int i);
int					fail_scheduler_mutex(t_dongle *dongles, int i);
int					fail_cond(t_dongle *dongles, int i);

// todo HELPERS FUNCTIONS FOR (heap.c)
void				heap_swap(t_request *c1, t_request *c2);
int					request_has_higher_priority(t_request *f, t_request *s,
						char *scheduler);

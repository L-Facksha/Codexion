/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codixion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azebahad <azebahad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 21:17:32 by azebahad          #+#    #+#             */
/*   Updated: 2026/07/27 15:00:17 by azebahad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

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

}					t_config;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;

}					t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	t_config		*config;

}					t_coder;

//todo PARSING:
int	parse_args(int ac, char **av, t_config *config);

//todo initialize INITIALIZE CODERS AND DONGLES
int	init_dongles(t_dongle *dongles, int count);
int	init_coders(t_coder *coders, t_dongle *dongles, t_config *config);

//todo SIMULATION
int	create_threads(t_coder *coders, t_config *config);

//todo CALCULATE TIME
long get_time_ms(void);

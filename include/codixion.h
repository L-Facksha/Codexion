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

}					t_config;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;

}					t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	t_config		*config;

}					t_coder;

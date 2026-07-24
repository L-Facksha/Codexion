typedef struct
{
    cord[8]
} t_cord;

// || (sch[i] >= 'A' && sch[i] <= 'Z')
typedef struct 
{
    int number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    char *scheduler;

}   t_config;
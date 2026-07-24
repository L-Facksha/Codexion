#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codixion.h"

int parse_nb(char *nb){
    int i = 0;
    while(nb[i]){
        if (nb[i] >= '0' && nb[i] <= '9')
            i++;
        else
            return -1;
    }
    long res = atoi((const char *)nb);
    if (res <= 0)
        return -1;
    return res;
}

char *parse_schedulare(char *sch){
    if (strcmp(sch, "fifo") == 0)
        return sch;
    else if (strcmp(sch, "edf") == 0)
        return sch;
    else
        return NULL;
}

int parse_args(int ac, char **av, t_config *config){
    if (ac != 9)
        return -1;
    
    int i;
    i = 1;
    while(i < ac - 1){
        int res = parse_nb(av[i]);
        if (res == -1)
            return -1;
        i++;
    }
    config->number_of_coders = parse_nb(av[1]);
    config->time_to_burnout = parse_nb(av[2]);
    config->time_to_compile = parse_nb(av[3]);
    config->time_to_debug = parse_nb(av[4]);
    config->time_to_refactor = parse_nb(av[5]);
    config->number_of_compiles_required = parse_nb(av[6]);
    config->dongle_cooldown = parse_nb(av[7]);
    char *test_sch;
    test_sch = parse_schedulare(av[8]);
    if (!test_sch)
        return -1;
    config->scheduler = test_sch;

    return 1;
}




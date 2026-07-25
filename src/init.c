#include "../include/codixion.h"
#include <stdlib.h>

int init_dongles(t_dongle *dongles, int count){
    int i;
    i = 0;
    while (i <= count){
        dongles[i].id = i;
        pthread_mutex_init(dongles[i].id, NULL);
        i++;
    }
}

int init_coders(t_coder *coders,
                t_dongle *dongles,
                t_config *config);
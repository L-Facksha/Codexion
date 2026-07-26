#include "../include/codixion.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    t_config   config;
    t_dongle   *dongles;
    t_coder    *coders;

    int x = parse_args(ac, av, &config);
    if (x != 1)
    {
        if (x == -1)
            printf("Error: Missing argument!\n");
        return (1);
    }

    dongles = malloc(sizeof(t_dongle) * config.number_of_coders);
    if (!dongles)
        return (1);

    coders = malloc(sizeof(t_coder) * config.number_of_coders);
    if (!coders)
    {
        free(dongles);
        return (1);
    }

    if (!init_dongles(dongles, config.number_of_coders))
        return (1);

    if (!init_coders(coders, dongles, &config))
        return (1);

    if (!create_threads(coders, &config))
        return (1);

    free(coders);
    free(dongles);

    return (0);
}
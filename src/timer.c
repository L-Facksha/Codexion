#include "../include/codixion.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

long get_time_ms(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == 0) {
        printf("Seconds: %ld\n", tv.tv_sec);
        printf("Microseconds: %ld\n", tv.tv_usec);
    } else {
        perror("gettimeofday failed");
    }
    return 0;
}

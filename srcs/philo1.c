#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>

long int    get_time(long int type)
{
    long int        time;
    struct timeval  te;
    
    gettimeofday(&te, NULL);
    if (type == 0)
        time = te.tv_sec*1000LL + te.tv_usec/1000;
    else
        time = (te.tv_sec*1000LL + te.tv_usec/1000) - type; 

    return (time);
}

int         main(int ac, char **av)
{
    long int    stime;

    stime = get_time(0);
    while (1)
    {
        printf("TIME : %ld\n", get_time(stime));
    }
}
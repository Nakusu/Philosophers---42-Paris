#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct  t_struct
{
    int nb philos;
    int teat;
    int tsleep;
    int tdo;
    int nbeat;
}               s_struct;

#endif
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
    int nbphilos;
    int tdie;
    int teat;
    int tsleep;
    int nbeat;
    int ids;
    int lock;
    int limit;
    pthread_mutex_t *eat_l;
    pthread_mutex_t talk;
}               s_struct;

void        ft_putchar(char caract);
void        ft_putstr(char *str);
void        ft_putnbr(int n);
long int    get_time(long int type);
void        ft_messages(int id, long int timestamp, int type, void *philos);


#endif
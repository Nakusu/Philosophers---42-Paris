#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
#include <unistd.h>

long int    get_time(long int type);
void        ft_putnbr(int n);
void        ft_putstr(char *str, int fd);
void        ft_putchar(char caract, int fd);
int         ft_check(char **str);
int         ft_isnum(char *str);
long long   ft_atoi(const char *str);
void        ft_start(void *global);
void        osleep(long int time);
char		*ft_itoa(long int n);
void	    *ft_calloc(size_t count, size_t size);

typedef struct s_philo
{
    int         id;
    int         eat;
    long int    last_eat;

}              t_philo;

typedef struct s_global
{
    int         maxthreads;
    int         threads;
    int         die;
    long int    timeDie;
    long int    timeEat;
    long int    tsleep;
    long int    t_start;
    int                 maxeats;
    pthread_mutex_t     talk;
    pthread_mutex_t     *keys;
    t_philo             *philos;
}             t_global;

#endif
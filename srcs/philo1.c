#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
#include <unistd.h>

void        ft_putchar(char caract)
{
    write(1, &caract, 1);
}

void        ft_putstr(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
}

long int    get_time(long int type)
{
    long int        time;
    struct timeval  te;
    
    gettimeofday(&te, NULL);
    if (type == 0)
        time = te.tv_sec * 1000LL + te.tv_usec/1000;
    else
        time = (te.tv_sec * 1000LL + te.tv_usec/1000) - type; 

    return (time);
}

int         ft_isnum(char *str)
{
    size_t i;

    i = 0;
    while (str && str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

void        ft_core(char *philos, char *t_die, char *t_eat, char *t_sleep, char *limit)
{
    long int    stime;

    if (!(ft_isnum(philos) && ft_isnum(t_die) && ft_isnum(t_eat) && ft_isnum(t_sleep) && ft_isnum(limit)))
        return ;
    stime = get_time(0);
    while (1)
    {
        printf("TIME : %ld\n", get_time(stime));
    }
}

int         main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        if (ac == 4)
            ft_core(av[1], av[2], av[3], av[4], 0);
        else
            ft_core(av[1], av[2], av[3], av[4], av[5]);
    }
    else
    {
        ft_putstr("Erreur : Veuillez lancer correctement le programme !\n");
        return (0);
    } 
    return (1);
}
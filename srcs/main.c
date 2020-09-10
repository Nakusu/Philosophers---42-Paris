#include "header.h"

int initGobal(char **str, int ac, t_global *global)
{
    global->maxeats = (ac == 5) ? -1 : ft_atoi(str[5]);
    global->threads = 0;
    if ((ac == 6 && global->maxeats <= 0) || (global->maxthreads = ft_atoi(str[1])) <= 0 || (global->timeDie = ft_atoi(str[2])) <= 0 || (global->timeEat = ft_atoi(str[3])) <= 0 || (global->tsleep = ft_atoi(str[4])) <= 0)
    {
        ft_putstr("Error : launch correctly the program !\n", 2);
        return (0);
    }
    pthread_mutex_init(&global->talk, NULL);
    pthread_mutex_unlock(&global->talk);
    return (1);
}

void    ft_tmessage(int type)
{
    if (type == 1)
        ft_putstr(" is launch !\n", 1);
    else if (type == 2)
        ft_putstr(" is die !\n", 1);
    else if (type == 3)
        ft_putstr(" is eating !\n", 1);
    else if (type == 4)
        ft_putstr(" is sleeping ! \n", 1);
    
}

void    ft_messages(int id, long int timestamp, t_global *global, char *message)
{
    if (pthread_mutex_lock(&global->talk) == 0)
    {
        ft_putnbr(timestamp);
        ft_putstr(" ", 1);
        ft_putnbr(id);
        ft_putstr(" ", 1);
        ft_putstr(message, 1);
        ft_putstr("\n", 1);
        pthread_mutex_unlock(&global->talk);
    }
}

void    *ft_jobs(void *global)
{
    t_global     *info;
    int         id;
    long int    stime;

    info = (t_global*)global;
    id = info->threads;
    ft_messages(id, 0, info, "was launch");
    stime = get_time(0);
    while (1)
    {
        ft_messages(id, get_time(stime), info, "CHECK !!");
        usleep(10);
    }
    return (global);
}

void    ft_core(t_global *global)
{
    int i;
    pthread_t   tid;

    i = 0;
    printf("MAX : %d\n", global->maxthreads);
    while (i < global->maxthreads)
    {
        if (pthread_create(&tid, NULL, ft_jobs, global) != 0)
            return ;
        pthread_detach(tid);
        global->threads += 1;
        usleep(200);
        i++;
    }
}

int     main(int ac, char **av)
{ 
    if (ac == 5 || ac == 6)
    {
        t_global global;
        if (initGobal(av, ac, &global) == 0)
            return (0);
        ft_core(&global);
        while (1);
        return (1);
    }
    ft_putstr("Error : launch correctly the program !\n", 2);
    return (1);
}
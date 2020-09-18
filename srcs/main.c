#include "header.h"

void initKeys(t_global *global)
{
    size_t i;

    i = 0;
    if (!(global->keys = malloc(sizeof(pthread_mutex_t) * global->maxthreads)))
        return ;
    while (i < global->maxthreads)
    {
        pthread_mutex_init(&global->keys[i], NULL);
        pthread_mutex_unlock(&global->keys[i]);
        i++;
    }
}

int initGobal(char **str, int ac, t_global *global)
{
    global->maxeats = (ac == 5) ? -1 : ft_atoi(str[5]);
    global->threads = 0;
    global->die = 0;
    global->t_start = get_time(0);
    if ((ac == 6 && global->maxeats <= 0) || (global->maxthreads = ft_atoi(str[1])) <= 0 || (global->timeDie = ft_atoi(str[2])) <= 0 || (global->timeEat = ft_atoi(str[3])) <= 0 || (global->tsleep = ft_atoi(str[4])) <= 0)
    {
        ft_putstr("Error : launch correctly the program !\n", 2);
        return (0);
    }
    if (!(global->philos = malloc((sizeof(t_philo) * global->maxthreads))))
    {
        ft_putstr("Error : malloc problem !\n", 2);
        return (0);
    }
    pthread_mutex_init(&global->talk, NULL);
    pthread_mutex_unlock(&global->talk);
    initKeys(global);
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

char    *ft_completestr(char *str, char *src)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    str[i++] = ' ';
    while (src[j])
    {
        str[i] = src[j];
        i++;
        j++;
    }
    str[i] = '\n';
    return (str);
}

void    ft_messages(int id, long int timestamp, t_global *global, char *message)
{
    char    *tmp;

    if (!(tmp = ft_calloc((ft_strlen(message) + 3), sizeof(char))))
        return ;
    if (pthread_mutex_lock(&global->talk) == 0)
    {
        ft_putstr(ft_itoa(timestamp), 1);
        ft_putchar(' ', 1);
        ft_putstr(ft_itoa(id), 1);
        ft_putstr(ft_completestr(tmp, message), 1);
        free(tmp);
        pthread_mutex_unlock(&global->talk);
    }
}

void    ft_eat(t_philo *philo, long int timestamp, t_global *global)
{
    int i;

    i = 0;
    i = (philo->id == 0) ? global->maxthreads - 1 : -1 ;
    if (pthread_mutex_lock(&global->keys[philo->id]) == 0 && pthread_mutex_lock(&global->keys[philo->id + i]) == 0)
    {
        ft_messages(philo->id, timestamp, global, "is eating !");
        philo->last_eat = get_time(0);
        osleep(global->timeEat);
        pthread_mutex_unlock(&global->keys[philo->id]);
        pthread_mutex_unlock(&global->keys[philo->id + i]);
    }
}


void    ft_sleep(t_philo *philo, long int timestamp, t_global *global)
{
        ft_messages(philo->id, timestamp, global, "is sleeping !");
        osleep(global->tsleep);
}

void    *ft_jobs(void *global)
{
    t_global    *info;
    long int    time;
    int         i;

    info = (t_global*)global;
    i = info->threads;
    info->philos[i].id = info->threads;
    ft_messages(i, get_time(info->t_start), info, "was launch");
    info->philos[i].last_eat = get_time(0);
    while (info->die == 0)
    {
        time = get_time(info->t_start);
        ft_eat(&info->philos[i], time, info);
        ft_sleep(&info->philos[i], time, info);
        ft_messages(info->philos[i].id, time, global, "is thinking !");
    }
    return (global);
}

void    ft_core(t_global *global)
{
    int i;
    pthread_t   tid;

    i = 0;
    while (i < global->maxthreads)
    {
        if (pthread_create(&tid, NULL, ft_jobs, global) != 0)
            return ;
        pthread_detach(tid);
        global->threads += 1;
        osleep(5);
        i++;
    }
}

void    ft_monitoring(t_global *global)
{
    size_t i;

    while (global->die == 0)
    {
        i = 0;
        while (i < global->maxthreads && global->die == 0)
        {
            if (global->philos[i].last_eat > 0 && get_time(global->philos[i].last_eat) > global->timeDie)
            {
                //printf("%ld\n", global->philos[i].last_eat);
                ft_messages(global->philos[i].id, get_time(global->t_start), global, "is die !");
                global->die += 1;
            }
            i++;
        }
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
        ft_monitoring(&global);
        return (1);
    }
    ft_putstr("Error : launch correctly the program !\n", 2);
    return (1);
}
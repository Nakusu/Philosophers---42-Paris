/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:43 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 14:57:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void initphilos(t_global *global)
{
    int     i;
    char    *tmp;

    i = 0;
    if (!(global->philos = malloc((sizeof(t_philo) * global->maxthreads))))
    {
        ft_putstr("Error : malloc problem !\n", 2);
        return ;
    }
    while (i < global->maxthreads)
    {
        tmp = ft_itoa(i);
        global->philos[i].id = i;
        global->philos[i].eat = 0;
        global->philos[i].last_eat = 0;
        global->philos[i].global = global;
        global->philos[i].lock = launch_sem(tmp, 1);
        free(tmp);
        i++;
    }
}

int initGobal(char **str, int ac, t_global *global)
{
    global->maxeats = (ac == 5) ? -1 : ft_atoi(str[5]);
    global->threads = 0;
    global->die = 0;
    global->t_start = get_time(0);
    global->eats = 0;
    if ((ac == 6 && global->maxeats <= 0) || (global->maxthreads = ft_atoi(str[1])) <= 0 || (global->timeDie = ft_atoi(str[2])) <= 0 || (global->timeEat = ft_atoi(str[3])) <= 0 || (global->tsleep = ft_atoi(str[4])) <= 0)
    {
        ft_putstr("Error : launch correctly the program !\n", 2);
        return (0);
    }
    initphilos(global);
    global->talk = launch_sem("TALK", 1);
    global->keys = launch_sem("KEYS", global->maxthreads);
    return (1);
}

void    ft_eat(t_philo *philo)
{
    t_global *global;

    global = philo->global;
    sem_wait(global->keys);
    ft_messages(philo, "as taking a fork !");
    sem_wait(global->keys);
    sem_wait(philo->lock);
    philo->last_eat = get_time(0);
    ft_messages2(philo, "is eating !");
    osleep(global->timeEat);
    sem_post(philo->lock);
    if (philo->global->maxeats > 0 && (philo->eat + 1) == philo->global->maxeats)
    {
        philo->eat += 2;
        philo->global->eats += 1;
    } 
    else if (philo->global->maxeats > 0)
        philo->eat += 1;
    sem_post(global->keys);
    sem_post(global->keys);
}


void    ft_sleep(t_philo *philo)
{
    ft_messages(philo, "is sleeping !");
    osleep(philo->global->tsleep);
}

void    *ft_jobs(void *args)
{
    t_global    *global;
    t_philo     *philo;
    pthread_t   t_monitoring;

    philo = (t_philo *)args;
    global = philo->global;
    if (pthread_create(&t_monitoring, NULL, monitoring, args) != 0)
        return (global);
    pthread_detach(t_monitoring);
    philo->last_eat = get_time(0);
    while (global->die == 0)
    {
        ft_eat(philo);
        ft_sleep(philo);
        ft_messages(philo, "is thinking !");
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
        if (pthread_create(&tid, NULL, ft_jobs, &global->philos[i]) != 0)
            return ;
        pthread_detach(tid);
        osleep(1);
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
        ft_globalmoni(&global);
        clearall(&global);
        return (1);
    }
    ft_putstr("Error : launch correctly the program !\n", 2);
    return (1);
}
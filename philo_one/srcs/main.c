/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:09:33 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 14:28:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void initKeys(t_global *global)
{
    int i;

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

void initphilos(t_global *global)
{
    int i;

    i = 0;
    if (!(global->philos = malloc((sizeof(t_philo) * global->maxthreads))))
    {
        ft_putstr("Error : malloc problem !\n", 2);
        return ;
    }
    while (i < global->maxthreads)
    {
        global->philos[i].id = i;
        global->philos[i].eat = 0;
        global->philos[i].last_eat = 0;
        global->philos[i].global = global;
        pthread_mutex_init(&global->philos[i].lock, NULL);
        pthread_mutex_unlock(&global->philos[i].lock);
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
    initphilos(global);
    pthread_mutex_init(&global->talk, NULL);
    pthread_mutex_unlock(&global->talk);
    initKeys(global);
    return (1);
}

void    ft_eat(t_philo *philo)
{
    int      i;
    t_global *global;

    global = philo->global;
    i = (philo->id == 0) ? global->maxthreads - 1 : -1 ;
    if (pthread_mutex_lock(&global->keys[philo->id + i]) == 0)
    {
        ft_messages(philo, "as taking a fork !");
        if (pthread_mutex_lock(&global->keys[philo->id]) == 0)
        {
            if (pthread_mutex_lock(&philo->lock) == 0)
            {
                philo->last_eat = get_time(0);
                ft_messages2(philo, "is eating !");
                philo->eat += 1;
                osleep(global->timeEat);
                pthread_mutex_unlock(&global->keys[philo->id]);
                pthread_mutex_unlock(&global->keys[philo->id + i]);
                pthread_mutex_unlock(&philo->lock);
            }
        }
    }
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
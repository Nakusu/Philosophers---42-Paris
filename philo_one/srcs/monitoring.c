/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:40 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 14:29:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    *monitoring(void *args)
{
   t_philo  *philo;
   t_global *global;

   philo = (t_philo *)args;
   global = philo->global;
    while (global->die == 0)
    {
        if (pthread_mutex_lock(&philo->lock) == 0)
        {
            if (get_time(philo->last_eat) > global->timeDie)
            {
                ft_messages(philo, "is die !");
                global->die += 1;
            }
            pthread_mutex_unlock(&philo->lock);
        }
        osleep(1);
    }
    return (args);
}

void    ft_globalmoni(t_global *global)
{
    int i;
    int v;

    while (global->die == 0)
    {
        i = 0;
        v = 0;
        while (i < global->maxthreads && global->maxeats > 0)
            if (global->philos[i++].eat == global->maxeats)
                v++;
        if (v == (global->maxthreads - 1))
            return ;
    }
}

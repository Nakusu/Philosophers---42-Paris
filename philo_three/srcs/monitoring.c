/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:40 by user42            #+#    #+#             */
/*   Updated: 2020/09/23 19:16:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			*monitoring(void *args)
{
	t_philo		*philo;
	t_global	*global;

	philo = (t_philo *)args;
	global = philo->global;
	while (global->die == 0)
	{
		if (sem_wait(philo->lock) == 0)
		{
			if (get_time(philo->last_eat) > global->timedie)
			{
				global->die += 1;
				ft_messages(philo, "died");
				sem_post(global->lock);
			}
			sem_post(philo->lock);
		}
		osleep(1);
	}
	return (args);
}

void			*ft_globalmoni(void *args)
{
	t_global 	*global;
	int			i;

	i = 0;
	global = (t_global*)args;
	while (i < global->maxthreads)
	{
		sem_wait(global->philos[i].lockeat);
		i++;
	}
	sem_post(global->lock);
	return (global);
}

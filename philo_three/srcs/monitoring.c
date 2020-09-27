/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:40 by user42            #+#    #+#             */
/*   Updated: 2020/09/27 14:51:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_messagesend(t_philo *philo, char *message)
{
	if (philo->global->die == 0)
	{
		sem_wait(philo->global->talk);
		philo->global->die += 1;
		ft_printmsg(philo, message);
	}
}

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
				ft_messagesend(philo, "died");
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
	t_global	*global;
	int			i;

	i = 0;
	global = (t_global*)args;
	if (global->maxeats != -1)
	{
		while (i < global->maxthreads)
		{
			sem_wait(global->philos[i].lockeat);
			i++;
		}
		global->die += 1;
		sem_post(global->lock);
	}
	return (global);
}

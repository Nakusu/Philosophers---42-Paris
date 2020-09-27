/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:40 by user42            #+#    #+#             */
/*   Updated: 2020/09/27 14:43:00 by user42           ###   ########.fr       */
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

void	*monitoring(void *args)
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
				ft_messagesend(philo, "died");
			sem_post(philo->lock);
		}
		osleep(1);
	}
	return (args);
}

void	ft_globalmoni(t_global *global)
{
	while (global->die == 0)
		if (global->eats == global->maxthreads && global->maxeats != -1)
		{
			global->die += 1;
			return ;
		}
}

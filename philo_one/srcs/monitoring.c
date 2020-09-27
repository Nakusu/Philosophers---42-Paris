/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:40 by user42            #+#    #+#             */
/*   Updated: 2020/09/27 16:14:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_messagesend(t_philo *philo, char *message)
{
	if (philo->global->die == 0)
	{
		pthread_mutex_lock(&philo->global->talk);
		philo->global->die += 1;
		ft_printmsg(philo, message);
	}
}

void	*monitoring(void *args)
{
	t_philo			*philo;
	t_global		*global;

	philo = (t_philo *)args;
	global = philo->global;
	while (global->die == 0)
	{
		if (pthread_mutex_lock(&philo->lock) == 0)
		{
			if (get_time(philo->last_eat) > global->timedie)
				ft_messagesend(philo, "died");
			pthread_mutex_unlock(&philo->lock);
		}
		osleep(1);
	}
	return (args);
}

void	ft_globalmoni(t_global *global)
{
	while (global->die == 0)
		if (global->eats == global->maxthreads && global->maxeats > 0)
		{
			global->die += 1;
			return ;
		}
}

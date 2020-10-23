/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:31:22 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:06:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	ft_last_message(t_philo *philo, char *message)
{
	if (philo->global->die == 0)
	{
		sem_wait(philo->global->talk);
		philo->global->die += 1;
		ft_print_msg(philo, message);
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
			if (ft_get_time(philo->last_meal) > global->time_to_die)
				ft_last_message(philo, "died");
			sem_post(philo->lock);
		}
		ft_usleep(1);
	}
	return (args);
}

void	ft_global_monitoring(t_global *global)
{
	while (global->die == 0)
		if (global->eats == global->nb_philos && global->nb_max_meals != -1)
		{
			global->die += 1;
			return ;
		}
}

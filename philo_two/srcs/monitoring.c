/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:40 by user42            #+#    #+#             */
/*   Updated: 2020/09/26 17:44:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
			{
				global->die += 1;
				ft_messages(philo, "died");
			}
			sem_post(philo->lock);
		}
		osleep(1);
	}
	return (args);
}

void	ft_globalmoni(t_global *global)
{
	while (global->die == 0)
		if (global->eats == (global->maxthreads - 1) && global->maxeats > 0)
		{
			global->die += 1;
			return ;
		}
}

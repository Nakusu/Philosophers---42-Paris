/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:09:33 by user42            #+#    #+#             */
/*   Updated: 2020/09/23 11:00:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_eat(t_philo *philo)
{
	int			i;
	t_global	*global;

	global = philo->global;
	i = (philo->id == 0) ? global->maxthreads - 1 : -1;
	if (pthread_mutex_lock(&global->keys[philo->id + i]) == 0)
	{
		ft_messages(philo, "has taken a fork");
		pthread_mutex_lock(&global->keys[philo->id]);
		pthread_mutex_lock(&philo->lock);
		philo->last_eat = get_time(0);
		ft_messages2(philo, "is eating");
		if (philo->global->maxeats > 0 &&
		(philo->eat + 1) == philo->global->maxeats)
		{
			philo->eat += 2;
			philo->global->eats += 1;
		}
		else if (philo->global->maxeats > 0)
			philo->eat += 1;
		osleep(global->timeeat);
		pthread_mutex_unlock(&global->keys[philo->id]);
		pthread_mutex_unlock(&global->keys[philo->id + i]);
		pthread_mutex_unlock(&philo->lock);
	}
}

void	ft_sleep(t_philo *philo)
{
	ft_messages(philo, "is sleeping");
	osleep(philo->global->tsleep);
}

void	*ft_jobs(void *args)
{
	t_global	*global;
	t_philo		*philo;
	pthread_t	t_monitoring;

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
		ft_messages(philo, "is thinking");
	}
	return (global);
}

void	ft_core(t_global *global)
{
	int			i;
	pthread_t	tid;

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

int		main(int ac, char **av)
{
	t_global global;

	if (ac == 5 || ac == 6)
	{
		if (initgobal(av, ac, &global) == 0)
			return (0);
		ft_core(&global);
		ft_globalmoni(&global);
		clearall(&global);
		return (1);
	}
	ft_putstr("Error : launch correctly the program !\n", 2);
	return (1);
}

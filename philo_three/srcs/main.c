/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:43 by user42            #+#    #+#             */
/*   Updated: 2020/09/26 18:50:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_eat(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (sem_wait(global->keys) == 0 && sem_wait(philo->lock) == 0)
	{
		ft_messages(philo, "has taken a fork");
		sem_wait(global->keys);
		philo->last_eat = get_time(0);
		ft_messages2(philo, "is eating");
		philo->eat += 1;
		if (philo->eat == philo->global->maxeats)
			sem_post(philo->lockeat);
		osleep(global->timeeat);
		sem_post(philo->lock);
		sem_post(global->keys);
		sem_post(global->keys);
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
	pid_t		tid[global->maxthreads];
	pthread_t	t_monitoring;

	i = 0;
	if (pthread_create(&t_monitoring, NULL, ft_globalmoni, global) != 0)
		return ;
	pthread_detach(t_monitoring);
	while (i < global->maxthreads)
	{
		if (!(tid[i] = fork()))
			ft_jobs(&global->philos[i]);
		osleep(1);
		i++;
	}
	sem_wait(global->lock);
	i = 0;
	while (i < global->maxthreads)
		kill(tid[i++], SIGKILL);
}

int		main(int ac, char **av)
{
	t_global global;

	if (ac == 5 || ac == 6)
	{
		if (initgobal(av, ac, &global) == 0)
			return (0);
		ft_core(&global);
		clearall(&global);
		return (1);
	}
	ft_putstr("Error : launch correctly the program !\n", 2);
	return (1);
}

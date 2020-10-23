/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 10:01:46 by user42            #+#    #+#             */
/*   Updated: 2020/09/23 10:56:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initkeys(t_global *global)
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

void	initphilos(t_global *global)
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

int		initgobal(char **str, int ac, t_global *global)
{
	global->maxeats = (ac == 5) ? -1 : ft_atoi(str[5]);
	global->threads = 0;
	global->die = 0;
	global->t_start = get_time(0);
	global->eats = 0;
	if ((ac == 6 && global->maxeats <= 0) ||
	(global->maxthreads = ft_atoi(str[1])) <= 0 ||
	(global->timedie = ft_atoi(str[2])) <= 0 ||
	(global->timeeat = ft_atoi(str[3])) <= 0 ||
	(global->tsleep = ft_atoi(str[4])) <= 0)
	{
		ft_putstr("Error : launch correctly the program !\n", 2);
		return (0);
	}
	initphilos(global);
	pthread_mutex_init(&global->talk, NULL);
	pthread_mutex_unlock(&global->talk);
	initkeys(global);
	return (1);
}

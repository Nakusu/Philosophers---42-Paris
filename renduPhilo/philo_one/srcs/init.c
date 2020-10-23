/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:27:14 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:06:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	ft_init_keys(t_global *global)
{
	int i;

	i = -1;
	if (!(global->keys = malloc(sizeof(pthread_mutex_t) * global->nb_philos)))
		return ;
	while (++i < global->nb_philos)
	{
		pthread_mutex_init(&global->keys[i], NULL);
		pthread_mutex_unlock(&global->keys[i]);
		i++;
	}
}

void	ft_init_philos(t_global *global)
{
	int i;

	i = -1;
	if (!(global->philos = malloc((sizeof(t_philo) * global->nb_philos))))
	{
		ft_putstr("Error : Memory allocation failed\n", 2);
		return ;
	}
	while (++i < global->nb_philos)
	{
		global->philos[i].id = i;
		global->philos[i].eat = 0;
		global->philos[i].last_meal = 0;
		global->philos[i].global = global;
		pthread_mutex_init(&global->philos[i].lock, NULL);
		pthread_mutex_unlock(&global->philos[i].lock);
	}
}

int		ft_init_gbl(char **str, int ac, t_global *global)
{
	global->nb_max_meals = (ac == 5) ? -1 : ft_atoi(str[5]);
	global->threads = 0;
	global->die = 0;
	global->t_start = ft_get_time(0);
	global->eats = 0;
	if ((ac == 6 && global->nb_max_meals <= 0) ||
	(global->nb_philos = ft_atoi(str[1])) <= 0 ||
	(global->time_to_die = ft_atoi(str[2])) <= 0 ||
	(global->time_to_eat = ft_atoi(str[3])) <= 0 ||
	(global->time_to_sleep = ft_atoi(str[4])) <= 0)
	{
		ft_putstr("Error : The program hasn't been launched correctly.\n", 2);
		return (0);
	}
	ft_init_philos(global);
	pthread_mutex_init(&global->talk, NULL);
	pthread_mutex_unlock(&global->talk);
	ft_init_keys(global);
	return (1);
}

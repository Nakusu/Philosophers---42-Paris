/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:31:11 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:06:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void		ft_init_philos(t_global *global)
{
	int		i;
	char	*tmp;

	i = -1;
	if (!(global->philos = malloc((sizeof(t_philo) * global->nb_philos))))
	{
		ft_putstr("Error : Memory allocation failed\n", 2);
		return ;
	}
	while (++i < global->nb_philos)
	{
		tmp = ft_itoa(i);
		global->philos[i].id = i;
		global->philos[i].eat = 0;
		global->philos[i].last_meal = 0;
		global->philos[i].global = global;
		global->philos[i].lock = launch_sem(tmp, 1);
		free(tmp);
	}
}

int			ft_init_gbl(char **str, int ac, t_global *global)
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
	global->talk = launch_sem("TALK", 1);
	global->keys = launch_sem("KEYS", global->nb_philos);
	return (1);
}

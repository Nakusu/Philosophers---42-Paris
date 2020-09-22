/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:00:38 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 18:00:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		initphilos(t_global *global)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(global->philos = malloc((sizeof(t_philo) * global->maxthreads))))
	{
		ft_putstr("Error : malloc problem !\n", 2);
		return ;
	}
	while (i < global->maxthreads)
	{
		tmp = ft_itoa(i);
		global->philos[i].id = i;
		global->philos[i].eat = 0;
		global->philos[i].last_eat = 0;
		global->philos[i].global = global;
		global->philos[i].lock = launch_sem(tmp, 1);
		free(tmp);
		i++;
	}
}

int			initgobal(char **str, int ac, t_global *global)
{
	global->maxeats = (ac == 5) ? -1 : ft_atoi(str[5]);
	global->threads = 0;
	global->die = 0;
	global->t_start = get_time(0);
	global->eats = 0;
	if ((ac == 6 && global->maxeats <= 0) ||
	(global->maxthreads = ft_atoi(str[1])) <= 0 ||
	(global->timeDie = ft_atoi(str[2])) <= 0 ||
	(global->timeEat = ft_atoi(str[3])) <= 0 ||
	(global->tsleep = ft_atoi(str[4])) <= 0)
	{
		ft_putstr("Error : launch correctly the program !\n", 2);
		return (0);
	}
	initphilos(global);
	global->talk = launch_sem("TALK", 1);
	global->keys = launch_sem("KEYS", global->maxthreads);
	return (1);
}

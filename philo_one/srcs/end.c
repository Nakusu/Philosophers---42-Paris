/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:36 by user42            #+#    #+#             */
/*   Updated: 2020/09/23 09:52:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			clearall(t_global *global)
{
	int i;

	i = 0;
	while (i < global->maxthreads)
	{
		pthread_mutex_destroy(&global->keys[i]);
		pthread_mutex_destroy(&global->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&global->talk);
	free(global->keys);
	free(global->philos);
	return (1);
}

long int	get_time(long int type)
{
	long int		time;
	struct timeval	te;

	gettimeofday(&te, NULL);
	if (type == 0)
		time = te.tv_sec * 1000LL + te.tv_usec / 1000;
	else
		time = (te.tv_sec * 1000LL + te.tv_usec / 1000) - type;
	return (time);
}

void		osleep(long int time)
{
	long int		start;

	start = get_time(0);
	while (get_time(start) < time)
		usleep(1);
}

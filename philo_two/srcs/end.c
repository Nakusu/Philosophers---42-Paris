/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:36 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 16:27:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		clearall(t_global *global)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < global->maxthreads)
	{
		tmp = ft_itoa(i);
		sem_unlink(tmp);
		free(tmp);
		i++;
	}
	sem_unlink("KEYS");
	sem_unlink("TALK");
	free(global->philos);
	return (1);
}

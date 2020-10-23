/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:31:00 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:06:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int		ft_free_all(t_global *global)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < global->nb_philos)
	{
		tmp = ft_itoa(i);
		sem_unlink(tmp);
		free(tmp);
	}
	sem_unlink("KEYS");
	sem_unlink("TALK");
	free(global->philos);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 17:13:34 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 17:14:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long int						get_time(long int type)
{
	long int					time;
	struct timeval				te;

	gettimeofday(&te, NULL);
	if (type == 0)
		time = te.tv_sec * 1000LL + te.tv_usec / 1000;
	else
		time = (te.tv_sec * 1000LL + te.tv_usec / 1000) - type;
	return (time);
}

void							osleep(long int time)
{
	long int		start;

	start = get_time(0);
	while (get_time(start) < time)
		usleep(1);
}

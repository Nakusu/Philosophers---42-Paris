/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_messages.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:51 by user42            #+#    #+#             */
/*   Updated: 2020/09/23 10:51:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		*ft_completestr(char *str, char *src)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	str[i++] = ' ';
	while (src[j])
	{
		str[i] = src[j];
		i++;
		j++;
	}
	str[i++] = '\n';
	str[i] = 0;
	return (str);
}

char		*ft_completenbr(char *str, char *nb1, char *nb2)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < ft_strlen(nb1))
		str[j++] = nb1[i++];
	i = 0;
	str[j++] = ' ';
	while (i < ft_strlen(nb2))
		str[j++] = nb2[i++];
	str[j] = 0;
	return (str);
}

void		ft_printmsg(t_philo *philo, char *message)
{
	char	tmp[50];
	char	tmpnbr[50];

	ft_completenbr(tmpnbr,
	ft_itoa(get_time(philo->global->t_start))
	, ft_itoa(philo->id));
	ft_putstr(tmpnbr, 1);
	ft_putstr(ft_completestr(tmp, message), 1);
}

void		ft_messages(t_philo *philo, char *message)
{
	sem_wait(philo->global->talk);
	ft_printmsg(philo, message);
	sem_post(philo->global->talk);
}

void		ft_messages2(t_philo *philo, char *message)
{
	sem_wait(philo->global->talk);
	ft_printmsg(philo, "has taken a fork");
	ft_printmsg(philo, message);
	sem_post(philo->global->talk);
}

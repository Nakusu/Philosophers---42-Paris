/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:27:32 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:06:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void				ft_putnbr(int n)
{
	long int	val;

	val = n;
	if (val < 0)
	{
		ft_putchar('-', 1);
		val = -val;
	}
	if (val > 9)
	{
		ft_putnbr(val / 10);
		ft_putchar((val % 10) + '0', 1);
	}
	else
		ft_putchar(val + '0', 1);
}

void				ft_putchar(char caract, int fd)
{
	write(fd, &caract, 1);
}

int					ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void				ft_putstr(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:17:48 by user42            #+#    #+#             */
/*   Updated: 2020/09/22 18:02:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		ft_putchar(char caract, int fd)
{
	write(fd, &caract, 1);
}

size_t		ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		ft_putstr(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void		*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	if (count == 0)
		count = 1;
	if (!size || !(tmp = malloc(count * size)))
		return (NULL);
	while (i < count * size)
	{
		((unsigned char *)tmp)[i] = '\0';
		i++;
	}
	return (tmp);
}

void		ft_putnbr(int n)
{
	long int val;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:27:37 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:06:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

long long			ft_atoi(const char *str)
{
	long				i;
	long long			result;
	long long			signe;

	i = 0;
	signe = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (result * signe);
	return (result * signe);
}

int					ft_isnum(char *str)
{
	size_t i;

	i = 0;
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void				*ft_calloc(size_t count, size_t size)
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

static long int		ft_cnb(int n)
{
	long int r;

	r = 0;
	if (n < 0)
	{
		r++;
		n *= -1;
	}
	else if (n == 0)
		r++;
	while (n != 0)
	{
		n /= 10;
		r++;
	}
	return (r);
}

char				*ft_itoa(long int n)
{
	char		*result;
	long int	stock;
	int			i;

	i = (ft_cnb(n) - 1);
	stock = n;
	if (!(result = ft_calloc((size_t)ft_cnb(n) + 1, sizeof(char))))
		return (NULL);
	if (n < 0)
	{
		stock *= -1;
		result[0] = '-';
	}
	else if (n == 0)
		result[0] = '0';
	while (stock != 0)
	{
		result[i] = (stock % 10) + 48;
		stock /= 10;
		i--;
	}
	return (result);
}

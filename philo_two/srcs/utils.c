/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:47 by user42            #+#    #+#             */
/*   Updated: 2020/09/21 17:52:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

sem_t		*launch_sem(char *array, int i)
{
	sem_unlink(array);
	return (sem_open(array, O_CREAT | O_EXCL, 0644,i));
}

long long   ft_atoi(const char *str)
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

int         ft_isnum(char *str)
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

void        ft_putchar(char caract, int fd)
{
    write(fd, &caract, 1);
}

size_t      ft_strlen(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void            ft_putstr(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
}

static long int	ft_cnb(int n)
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


void	*ft_calloc(size_t count, size_t size)
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

char			*ft_itoa(long int n)
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

void         ft_putnbr(int n)
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

long int    get_time(long int type)
{
    long int        time;
    struct timeval  te;
    
    gettimeofday(&te, NULL);
    if (type == 0)
        time = te.tv_sec * 1000LL + te.tv_usec/1000;
    else
        time = (te.tv_sec * 1000LL + te.tv_usec/1000) - type; 

    return (time);
}

void        osleep(long int time)
{
    long int    start;

    start = get_time(0);
    while (get_time(start) < time)
        usleep(1);
    
}
#include "header.h"

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

void        ft_putstr(char *str, int fd)
{
    write(fd, str, ft_strlen(str));
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
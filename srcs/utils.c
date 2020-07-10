#include "philo.h"

void        ft_putchar(char caract)
{
    write(1, &caract, 1);
}

void        ft_putstr(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
}

void         ft_putnbr(int n)
{
    long int val;

    val = n;
    if (val < 0)
    {
        ft_putchar('-');
        val = -val;
    }
    if (val > 9)
    {
        ft_putnbr(val / 10);
        ft_putchar((val % 10) + '0');
    }
    else
        ft_putchar(val + '0');
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
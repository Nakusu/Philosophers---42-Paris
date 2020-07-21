#include "philo.h"

void    ft_tmessage(int type)
{
    if (type == 1)
        ft_putstr(" is launch !\n");
    else if (type == 2)
        ft_putstr(" is die !\n");
    else if (type == 3)
        ft_putstr(" is eating !\n");
    else if (type == 4)
        ft_putstr(" is sleeping ! \n");
    
}

void    ft_messages(int id, long int timestamp, int type, void *philos)
{
    s_struct *philo;

    philo = (s_struct*)philos;
    while (1)
    {
        if (pthread_mutex_lock(&philo->talk) == 0)
        {
            ft_putnbr(timestamp);
            ft_putchar(' ');
            ft_putnbr(id);
            ft_tmessage(type);
            pthread_mutex_unlock(&philo->talk);
            return ;
        }
    }
}
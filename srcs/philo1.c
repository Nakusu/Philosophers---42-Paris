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

int		ft_atoi(const char *str)
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

void        ft_work(int x)
{
    printf("Philo number %d was launch\n", x);
    usleep(1000000000);
    printf("Ok I'm back !\n");
}

void        ft_core(char *philos, char *t_die, char *t_eat, char *t_sleep, char *limit)
{
    long int    stime;
    pthread_t   tid;
    int         x;

    if (!(ft_isnum(philos) && ft_isnum(t_die) && ft_isnum(t_eat) && ft_isnum(t_sleep) && ft_isnum(limit)))
        return ;
    x = 0;
    stime = get_time(0);
    while (1)
    {
        if (ft_atoi(philos) > x)
        {
            pthread_create(&tid, NULL, ft_work, &x);
            printf("Launch\n");
            x++;
        }
        //printf("TIME : %ld\n", get_time(stime));
    }
}

int         main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        if (ac == 4)
            ft_core(av[1], av[2], av[3], av[4], 0);
        else
            ft_core(av[1], av[2], av[3], av[4], av[5]);
    }
    else
    {
        ft_putstr("Erreur : Veuillez lancer correctement le programme !\n");
        return (0);
    } 
    return (1);
}
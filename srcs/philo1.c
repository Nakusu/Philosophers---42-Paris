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

void        ft_work(void *philos)
{
    s_struct*   philo; 
    int         id;

    philo = (s_struct*)philos;
    id = philo->ids;
    philo->ids += 1;
    printf("ID %d\n", id);
    philo->lock = 0;
    while (1)
    {
        if (1 == 2)
        {
            printf("Ok I'm back !\n");
        }
    }
}

s_struct    ft_init(s_struct philos, char **av, int ac)
{
    if (ac == 5)
    {
        if (!(ft_isnum(av[1]) && ft_isnum(av[2]) && ft_isnum(av[3]) && ft_isnum(av[4])))
            return (philos);
        philos.nbphilos = ft_atoi(av[1]);
        philos.tdie = ft_atoi(av[2]);
        philos.teat = ft_atoi(av[3]);
        philos.tsleep = ft_atoi(av[4]);
        philos.ids = 0;
        philos.lock = 0;
    }
    else
    {
        if (!(ft_isnum(av[1]) && ft_isnum(av[2]) && ft_isnum(av[3]) && ft_isnum(av[4]) && ft_isnum(av[5])))
            return (philos);
        philos.nbphilos = ft_atoi(av[1]);
        philos.tdie = ft_atoi(av[2]);
        philos.teat = ft_atoi(av[3]);
        philos.tsleep = ft_atoi(av[4]);
        philos.nbeat = ft_atoi(av[5]);
        philos.ids = 0;
        philos.lock = 0;
    }
    return (philos);
}

void        ft_core(s_struct philos)
{
    long int    stime;
    pthread_t   tid;

    stime = get_time(0);
    while (1)
    {
        if (philos.nbphilos > philos.ids && philos.lock == 0)
        {
            philos.lock = 1;
            pthread_create(&tid, NULL, ft_work, (void*)&philos);
        }
        //printf("TIME : %ld\n", get_time(stime));
    }
}

int         main(int ac, char **av)
{
    s_struct philos;

    if (ac == 5 || ac == 6)
    {
        philos = ft_init(philos, av, ac);
        ft_core(philos);
    }
    else
    {
        ft_putstr("Erreur : Veuillez lancer correctement le programme !\n");
        return (0);
    } 
    return (1);
}
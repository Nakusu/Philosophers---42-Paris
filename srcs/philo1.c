#include "philo.h"

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
    long int    stime;
    long int    time;

    philo = (s_struct*)philos;
    stime = get_time(0);
    id = philo->ids;
    philo->ids += 1;
    ft_messages( id, 0, 1, philos);
    philo->lock = 0;
    while (1)
    {
        time = get_time(stime);
        if (time >= philo->tdie)
            break ;
    }
    ft_messages(id, time, 2, philos);
}

pthread_mutex_t     *ft_initf(pthread_mutex_t *array, size_t limit)
{
    size_t i;

    i = 0;
    if (!(array = malloc(sizeof(pthread_mutex_t) * (limit + 1))))
        return (NULL);
    while (i < limit)
    {
        pthread_mutex_init(&array[i], NULL);
        i++;
    }
    return (array);
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
        philos.limit = (philos.nbphilos / 2);
        philos.eat_l = ft_initf(philos.eat_l, philos.limit);
        pthread_mutex_init(&philos.talk, NULL);
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
        philos.eat_l = ft_initf(philos.eat_l, philos.limit);
        pthread_mutex_init(&philos.talk, NULL);
    }
    return (philos);
}

void        ft_core(s_struct philos)
{
    pthread_t   tid;

    while (1)
    {
        if (philos.nbphilos > philos.ids && philos.lock == 0)
        {
            philos.lock = 1;
            pthread_create(&tid, NULL, ft_work, (void*)&philos);
        }
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
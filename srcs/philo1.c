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

int         ft_eat(int id, void *philos, long int time)
{
    s_struct    *philo;
    size_t      i;

    philo = (s_struct*)philos;
    i = 0;
    while (i < (philo->nbphilos / 2))
    {
        if (pthread_mutex_trylock(&philo->eat_key[i]) == 0)
        {
            ft_messages( id, time, 3, philos);
            return (1);
        }
        i++;
    }
    return (0);
}

int         ft_uneat(int id, void *philos, long int time)
{
    s_struct    *philo;
    size_t      i;

    i = 0;
    philo = (s_struct*)philos;
    while (i < (philo->nbphilos / 2))
    {
        if (pthread_mutex_trylock(&philo->eat_key[i]) != 0)
        {
            pthread_mutex_unlock(&philo->eat_key[i]);
            ft_messages( id, time, 4, philos);
            philo->threads[id].lasteat = get_time(philo->threads[id].stime);
            return (1);
        }
        i++;
    }
    return (0);
}

void        ft_work(void *philos)
{
    s_struct    *philo; 
    int         id;
    long int    time;
    
    philo = (s_struct*)philos;
    id = philo->ids;
    philo->threads[id].stime = get_time(0);
    philo->ids += 1;
    ft_messages(id, 0, 1, philos);
    philo->lock = 0;
    while (1)
    {
        time = get_time(philo->threads[id].stime);
        if (ft_eat(id, philos, time))
        {
            usleep((philo->teat / 1000));
            if (ft_uneat(id, philos, time) == 1)
            {
                usleep((philo->tsleep / 1000));
                philo->threads[id].lasteat = get_time(0);
            }
        }
        if (philo->threads[id].lasteat > 0 && get_time(philo->threads[id].lasteat) >= philo->tdie) {
            //printf("CHECK %ld\n", philo->threads[id].lasteat);
            ft_messages(id, time, 2, philos);
            philo->status = 0;
            break ;
        }
    }
}

void        ft_core(s_struct philos)
{
    pthread_t   tid;

    while (philos.status == 1)
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
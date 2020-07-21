#include "philo.h"

pthread_mutex_t     *ft_initkey(pthread_mutex_t *array, size_t limit)
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

t_thread    *ft_initathread(s_struct philos)
{
    size_t      i;
    t_thread    *array;

    if (!(array = malloc(sizeof(t_thread) * (philos.nbphilos + 1))))
        return (NULL);
    array->lasteat = 0;
    array->stime = 0;
    return (array);
}

s_struct    ft_init(s_struct philos, char **av, int ac)
{
    if (ac == 5)
    {
        if (!(ft_isnum(av[1]) && ft_isnum(av[2]) && ft_isnum(av[3]) && ft_isnum(av[4])))
            return (philos);
        philos.status = 1;
        philos.nbphilos = ft_atoi(av[1]);
        philos.tdie = ft_atoi(av[2]);
        philos.teat = ft_atoi(av[3]);
        philos.tsleep = ft_atoi(av[4]);
        philos.ids = 0;
        philos.lock = 0;
        philos.eat_key = ft_initkey(philos.eat_key, (philos.nbphilos / 2));
        philos.threads = ft_initathread(philos);
        pthread_mutex_init(&philos.talk, NULL);
    }
    else
    {
        if (!(ft_isnum(av[1]) && ft_isnum(av[2]) && ft_isnum(av[3]) && ft_isnum(av[4]) && ft_isnum(av[5])))
            return (philos);
        philos.status = 1;
        philos.nbphilos = ft_atoi(av[1]);
        philos.tdie = ft_atoi(av[2]);
        philos.teat = ft_atoi(av[3]);
        philos.tsleep = ft_atoi(av[4]);
        philos.nbeat = ft_atoi(av[5]);
        philos.ids = 0;
        philos.lock = 0;
        philos.threads = ft_initathread(philos);
        philos.eat_key = ft_initkey(philos.eat_key, (philos.nbphilos / 2));
        pthread_mutex_init(&philos.talk, NULL);
    }
    return (philos);
}
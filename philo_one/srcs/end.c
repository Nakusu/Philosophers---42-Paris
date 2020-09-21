#include "header.h"

int     clearall(t_global *global)
{
    int i;

    i = 0; 
    while (i < global->maxthreads)
    {
        pthread_mutex_destroy(&global->keys[i]);
        pthread_mutex_destroy(&global->philos[i].lock);
        i++;
    }
    pthread_mutex_destroy(&global->talk);
    free(global->keys);
    free(global->philos);
    return (1);
}
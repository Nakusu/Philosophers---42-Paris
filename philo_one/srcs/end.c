/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:15:36 by user42            #+#    #+#             */
/*   Updated: 2020/09/21 13:15:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
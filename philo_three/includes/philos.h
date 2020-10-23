/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 11:07:33 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 11:08:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <inttypes.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>

typedef struct			s_philo
{
	int					id;
	int					eat;
	long int			last_meal;
	sem_t				*lock;
	sem_t				*lockeat;
	struct s_global		*global;
}						t_philo;

typedef struct			s_global
{
	int					nb_philos;
	int					threads;
	int					die;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			t_start;
	int					nb_max_meals;
	int					eats;
	sem_t				*talk;
	sem_t				*keys;
	sem_t				*lock;
	pid_t				*tids;
	t_philo				*philos;
}						t_global;

long int				ft_get_time(long int type);
void					ft_putnbr(int n);
void					ft_putstr(char *str, int fd);
void					ft_putchar(char caract, int fd);
int						ft_check(char **str);
int						ft_isnum(char *str);
long long				ft_atoi(const char *str);
void					ft_start(void *global);
void					ft_usleep(long int time);
char					*ft_itoa(long int n);
void					*ft_calloc(size_t count, size_t size);
size_t					ft_strlen(char *str);
char					*ft_construct_str(char *str, char *src);
void					ft_messages(t_philo *philo, char *message);
void					ft_messages2(t_philo *philo, char *message);
int						ft_free_all(t_global *global);
void					*monitoring(void *args);
void					*ft_global_monitoring(void *args);
sem_t					*launch_sem(char *array, int i);
int						ft_init_gbl(char **str, int ac, t_global *global);
void					ft_init_philos(t_global *global);
void					ft_print_msg(t_philo *philo, char *message);

#endif

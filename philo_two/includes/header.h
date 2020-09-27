/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 10:27:54 by user42            #+#    #+#             */
/*   Updated: 2020/09/27 13:55:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

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

typedef struct				s_philo
{
	int						id;
	int						eat;
	long int				last_eat;
	sem_t					*lock;
	struct s_global			*global;
}							t_philo;

typedef struct				s_global
{
	int						maxthreads;
	int						threads;
	int						die;
	long int				timedie;
	long int				timeeat;
	long int				tsleep;
	long int				t_start;
	int						maxeats;
	int						eats;
	sem_t					*talk;
	sem_t					*keys;
	t_philo					*philos;
}							t_global;

long int					get_time(long int type);
void						ft_putnbr(int n);
void						ft_putstr(char *str, int fd);
void						ft_putchar(char caract, int fd);
int							ft_check(char **str);
int							ft_isnum(char *str);
long long					ft_atoi(const char *str);
void						ft_start(void *global);
void						osleep(long int time);
char						*ft_itoa(long int n);
void						*ft_calloc(size_t count, size_t size);
size_t						ft_strlen(char *str);
char						*ft_completestr(char *str, char *src);
void						ft_messages(t_philo *philo, char *message);
void						ft_messages2(t_philo *philo, char *message);
int							clearall(t_global *global);
void						*monitoring(void *args);
void						ft_globalmoni(t_global *global);
sem_t						*launch_sem(char *array, int i);
void						initphilos(t_global *global);
int							initgobal(char **str, int ac, t_global *global);
char						*ft_itoa(long int n);
void						ft_messagesend(t_philo *philo, char *message);

#endif

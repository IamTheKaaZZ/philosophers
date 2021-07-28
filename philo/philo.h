/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:24:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/28 12:24:25 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# define TRUE 1
# define FALSE 0

typedef unsigned long	t_ul;
typedef int				t_bool;

typedef struct s_philo
{
	pthread_t		thread;
	int				position;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	t_bool			has_forks;
	t_bool			is_eating;
	t_bool			is_thinking;
	t_bool			is_asleep;
	t_bool			is_dead;
	t_ul			time_since_eat;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	eating_mutex;
}			t_philo;

typedef struct s_data
{
	t_ul			n_philos;
	t_ul			death_time;
	t_ul			eat_time;
	t_ul			sleep_time;
	t_ul			max_eat;
	t_ul			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	message_mutex;
	pthread_mutex_t	dead_mutex;
}					t_data;

/*
**	Init and error
*/

int		error_exit(t_data *d, char *errmessage, t_bool clear);
t_bool	error_and_init(t_data *d, int argc, char **argv);
void	init_philos(t_philo *philos, int n_philos);
t_bool	init_mutexes(t_data	*d);

/*
**	Helper functions
*/

int		ft_atoi(const char *numstr);
size_t	ft_strlen(const char *str);

#endif

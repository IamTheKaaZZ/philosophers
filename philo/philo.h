/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:24:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/29 13:29:54 by bcosters         ###   ########.fr       */
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
# define ONE_MS 1000

typedef unsigned long	t_ul;
typedef int				t_bool;

typedef enum s_status
{
	TOOK_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FULL_END
}	t_status;

typedef struct s_philo
{
	pthread_t		thread;
	int				position;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	t_status		status;
	t_ul			start_time;
	t_ul			time_to_die;
	t_ul			time_since_eat;
	t_ul			new_death_time;
	pthread_mutex_t	philo_mutex;
}			t_philo;

typedef struct s_table
{
	int				n_philos;
	t_ul			death_time;
	t_ul			eat_time;
	t_ul			sleep_time;
	t_ul			max_eat;
	t_ul			start_time;
	t_philo			*philos;
	t_philo			current_philo;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	message_mutex;
}					t_table;

/*
**	Init and error
*/

int		error_exit(t_table *t, char *errmessage, t_bool clear);
t_bool	error_and_init(t_table *t, int argc, char **argv);
void	init_philos(t_table *t, t_philo *philos, int n_philos);
t_bool	init_mutexes(t_table *t);
void	clear_data(t_table *t);

/*
**	Helper functions
*/

int		ft_atoi(const char *numstr);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_ulong_fd(t_ul n, int fd);
t_ul	get_current_time(void);

#endif

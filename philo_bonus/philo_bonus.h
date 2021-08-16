/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:24:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/16 11:54:19 by bcosters         ###   ########.fr       */
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
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "ft_ansi.h"
# define TRUE 1
# define FALSE 0
# define ONE_MS 1000
# define LOCK_SEMA "pSemLock"
# define FORK_SEMA "pSemFork"
# define MESSAGE_SEMA "pSemMessage"

typedef long long		t_ll;
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
	int			pid;
	int			id;
	int			eat_count;
	t_status	status;
	t_ll		start_time;
	t_ll		time_to_eat;
	t_ll		time_to_sleep;
	t_ll		time_to_die;
	t_ll		new_death_time;
	// t_bool		*left_fork_taken;
	// t_bool		*right_fork_taken;
	t_bool		*somebody_is_dead;
	sem_t		*lock_sem;
	sem_t		*forks_sem;
	sem_t		*message_sem;
}					t_philo;

typedef struct s_table
{
	int			n_philos;
	t_ll		death_time;
	t_ll		eat_time;
	t_ll		sleep_time;
	t_ll		max_eat;
	t_philo		*philos;
	t_bool		somebody_died;
	// t_bool		*taken_forks;
	sem_t		*forks_sem;
	sem_t		message_sem;
}					t_table;

/*
**	Init and error
*/

int		error_exit(t_table *t, char *errmessage, t_bool clear);
t_bool	error_and_init(t_table *t, int argc, char **argv);
t_bool	init_philos(t_table *t, t_philo *philos, int n_philos);
t_bool	init_mutexes(t_table *t);
void	clear_data(t_table *t);

/*
**	Helper functions
*/

int		ft_atoi(const char *numstr);
t_ll	get_time_elapsed(void);
t_ll	get_current_time(t_ll start_time);

/*
**	Philosopher functions
*/
void	message_printer(t_philo *philo);
t_bool	check_death(t_philo *p);
void	take_forks(t_philo *philo);
void	put_fork_down(sem_t	 *fork, t_bool *taken);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:24:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 14:07:23 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <signal.h>
# include "ft_ansi.h"
# define TRUE 1
# define FALSE 0
# define ONE_MS 1000
# define FORK_SEMA "pSemFork"
# define MESSAGE_SEMA "pSemMessage"
# define END_SEMA "pSemEnd"
# define TIME_SEMA "pSemTime"
# define FULL_SEMA "pSemFull"

typedef long long		t_ll;
typedef unsigned long	t_ul;
typedef int				t_bool;

typedef enum e_status
{
	TOOK_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_status;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	int			eat_count;
	t_ll		start_time;
	t_ll		time_to_eat;
	t_ll		time_to_sleep;
	t_ll		time_to_die;
	t_ll		time_ate;
	sem_t		*forks_sem;
	sem_t		*message_sem;
	char		*sema_name;
	sem_t		*time_sem;
	sem_t		*full_sem;
	sem_t		*end_sem;
}				t_philo;

typedef struct s_table
{
	int			n_philos;
	t_ll		death_time;
	t_ll		eat_time;
	t_ll		sleep_time;
	t_ll		max_eat;
	t_philo		*philos;
	sem_t		*forks_sem;
	sem_t		*message_sem;
	sem_t		*end_sem;
	sem_t		*full_sem;
}				t_table;

/*
**	Init and error
*/

int		my_perror(const char *str);
int		error_exit(t_table *t, char *errmessage, t_bool clear);
t_bool	error_and_init(t_table *t, int argc, char **argv);
t_bool	init_philos(t_table *t, t_philo *philos, int n_philos);
t_bool	init_semaphores(t_table *t);
char	*make_named_sema(char const *prefix, int id);
t_bool	sem_open_check(sem_t **semaphore, char *name, int value);
t_bool	open_and_close(sem_t *semaphore, char *name, int value);
t_bool	unlink_semaphore(const char *name);
void	clear_data(t_table *t);

/*
**	Helper functions
*/

int		ft_atoi(const char *numstr);
size_t	ft_strlen(const char *str);
t_ll	get_time_elapsed(void);
t_ll	get_current_time(t_ll start_time);
t_bool	countdown(t_philo *philo, t_ll end_time);

/*
**	Philosopher functions
*/
void	message_printer(t_philo *philo, int status);
t_bool	check_death(t_philo *p);
void	*death_routine(void *p);
void	open_semaphores(t_philo *p);
void	philosophy_routine(t_philo *p);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	*full_routine(void *table);
void	*end_routine(void *table);

#endif

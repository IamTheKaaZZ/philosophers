/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:22:16 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/23 19:13:02 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static t_bool	setup_table(t_table *t, int argc, char **argv)
{
	memset(t, 0, sizeof(t_table));
	t->n_philos = ft_atoi(argv[1]);
	t->death_time = ft_atoi(argv[2]);
	t->eat_time = ft_atoi(argv[3]);
	t->sleep_time = ft_atoi(argv[4]);
	if (t->n_philos < 1 || t->n_philos > 200)
		return (my_perror("Too little or too many Philosophers.\n"));
	if (t->death_time < 0)
		return (my_perror("(Death time < 0) No immortality.\n"));
	if (t->eat_time < 0)
		return (my_perror("(Eat time < 0) No time travelling.\n"));
	if (t->sleep_time < 0)
		return (my_perror("(Sleep time < 0) Philosopher != Student.\n"));
	if (argc == 6)
	{
		t->max_eat = ft_atoi(argv[5]);
		if (t->max_eat < 0)
			return (my_perror("(Must eat < 0) (┛ಠ_ಠ)┛彡┻━┻ No spaghetti.\n"));
	}
	else
		t->max_eat = -1;
	return (0);
}

t_bool	error_and_init(t_table *t, int argc, char **argv)
{
	if (argc != 6)
	{
		if (argc < 5)
			return (my_perror("Not enough arguments.\n"));
		else if (argc > 6)
			return (my_perror("Too many arguments.\n"));
	}
	if (setup_table(t, argc, argv))
		return (my_perror("Given arguments are invalid.\n"));
	t->philos = (t_philo *)malloc(t->n_philos * sizeof(t_philo));
	if (!t->philos)
		return (my_perror("Malloc fail.\n"));
	return (0);
}

/*
	Handled the 1 philo edge case here instead.
*/

t_bool	init_philos(t_table *t, t_philo *philos, int n_philos)
{
	int	i;

	i = -1;
	while (++i < n_philos)
	{
		philos[i].id = i;
		philos[i].eat_count = t->max_eat;
		if (n_philos == 1)
			philos[i].status = TOOK_FORK;
		else
			philos[i].status = THINKING;
		philos[i].start_time = 0;
		philos[i].time_to_eat = t->eat_time;
		philos[i].time_to_sleep = t->sleep_time;
		philos[i].time_to_die = t->death_time;
		philos[i].new_death_time = t->death_time;
		philos[i].somebody_is_dead = &t->somebody_died;
	}
	return (0);
}

/*
	~~	The following functions open the shared named semaphores	~~
	-> Named semaphores are shared in memory by:
		the parent and any child processes
	The semaphores will not be used by the parent:
	->	The parent opens them for the child processes to use later.
		-> Checks for sem_open failure
	-> The parent then closes the semaphore for itself since it doesn't need it
		-> Checks for sem_close failure
		-> Unlinks the semaphore completely in case of failure
*/

static t_bool	open_and_close(sem_t *semaphore, char *name, int value)
{
	semaphore = sem_open(name, O_CREAT | O_EXCL, 0600, value);
	if (semaphore == SEM_FAILED)
		return (my_perror("Opening named semaphore.\n"));
	if (sem_close(semaphore) < 0)
	{
		sem_unlink(name);
		return (my_perror("Closing named semaphore.\n"));
	}
	return (0);
}

/*
	The forks_sema gets initialized with a value of n_philos / 2
	=> 2 forks per philo
	=> semaphore only needs to be accessed once per time they want forks
*/

t_bool	init_semaphores(t_table *t)
{
	sem_unlink(MESSAGE_SEMA);
	sem_unlink(FORK_SEMA);
	if (open_and_close(t->message_sem, MESSAGE_SEMA, 1))
		return (1);
	if (open_and_close(t->forks_sem, FORK_SEMA, t->n_philos / 2))
		return (1);
	return (0);
}

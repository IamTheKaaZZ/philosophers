/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:44:01 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 14:39:52 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_bool	sem_open_check(sem_t **semaphore, char *name, int value)
{
	*semaphore = sem_open(name, O_CREAT | O_EXCL, 0600, value);
	if (*semaphore == SEM_FAILED)
		return (my_perror("Opening named semaphore.\n"));
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

t_bool	open_and_close(sem_t *semaphore, char *name, int value)
{
	if (sem_open_check(&semaphore, name, value))
		return (1);
	if (sem_close(semaphore) < 0)
	{
		sem_unlink(name);
		return (my_perror("Closing named semaphore.\n"));
	}
	return (0);
}

/*
	The forks_sema gets initialized with a value of n_philos
	=> 2 forks per philo
*/

t_bool	init_semaphores(t_table *t)
{
	sem_unlink(MESSAGE_SEMA);
	sem_unlink(FORK_SEMA);
	sem_unlink(END_SEMA);
	sem_unlink(FULL_SEMA);
	if (open_and_close(t->message_sem, MESSAGE_SEMA, 1))
		return (1);
	if (open_and_close(t->forks_sem, FORK_SEMA, t->n_philos))
		return (1);
	if (sem_open_check(&t->end_sem, END_SEMA, 0))
		return (1);
	if (sem_open_check(&t->full_sem, FULL_SEMA, 0))
		return (1);
	return (0);
}

t_bool	unlink_semaphore(const char *name)
{
	if (sem_unlink(name) < 0)
		return (my_perror("sem_unlink failure.\n"));
	return (0);
}

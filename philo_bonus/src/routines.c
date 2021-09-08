/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:30:02 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 15:19:18 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	open_semaphores(t_philo *p)
{
	p->message_sem = sem_open(MESSAGE_SEMA, O_RDWR);
	if (p->message_sem == SEM_FAILED)
		exit(unlink_semaphore(MESSAGE_SEMA) + 1);
	p->forks_sem = sem_open(FORK_SEMA, O_RDWR);
	if (p->forks_sem == SEM_FAILED)
		exit(unlink_semaphore(FORK_SEMA) + 1);
	p->end_sem = sem_open(END_SEMA, O_RDWR);
	if (p->end_sem == SEM_FAILED)
		exit(unlink_semaphore(END_SEMA) + 1);
	p->full_sem = sem_open(FULL_SEMA, O_RDWR);
	if (p->full_sem == SEM_FAILED)
		exit(unlink_semaphore(FULL_SEMA) + 1);
}

void	philosophy_routine(t_philo *p)
{
	pthread_t	death_checker;

	open_semaphores(p);
	if (pthread_create(&death_checker, NULL, death_routine, (void *)p) != 0)
		exit(EXIT_FAILURE);
	while (p->eat_count != 0)
	{
		take_forks(p);
		eating(p);
		sleeping(p);
		message_printer(p, THINKING);
	}
	if (pthread_join(death_checker, NULL) != 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

/*
*	Wait until everyone is full, then post the end_sem
*/

void	*full_routine(void *table)
{
	t_table	*t;
	int		i;

	t = (t_table *)table;
	i = -1;
	while (++i < t->n_philos)
		sem_wait(t->full_sem);
	sem_post(t->end_sem);
	return (NULL);
}

/*
 *	KILL THEM ALL
 *	+ clean up full routine if it exists
*/

void	*end_routine(void *table)
{
	t_table	*t;
	int		i;

	t = (t_table *)table;
	sem_wait(t->end_sem);
	i = -1;
	while (++i < t->n_philos)
		sem_post(t->full_sem);
	i = -1;
	while (++i < t->n_philos)
		kill(t->philos[i].pid, SIGTERM);
	return (NULL);
}

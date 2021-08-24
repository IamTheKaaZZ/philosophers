/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:30 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/24 14:31:03 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_bool	unlink_semaphore(const char *name)
{
	if (sem_unlink(name) < 0)
		return (my_perror("sem_unlink failure.\n"));
	return (0);
}

void	open_semaphores(t_philo *p)
{
	p->message_sem = sem_open(MESSAGE_SEMA, O_RDWR);
	if (p->message_sem == SEM_FAILED)
		exit(unlink_semaphore(MESSAGE_SEMA) + 1);
	p->forks_sem = sem_open(FORK_SEMA, O_RDWR);
	if (p->forks_sem == SEM_FAILED)
		exit(unlink_semaphore(FORK_SEMA) + 1);
}

void	exit_child(t_philo *p)
{
	if (sem_close(p->message_sem) < 0 || sem_close(p->forks_sem) < 0)
		exit(my_perror("Closing semaphores failure in child.\n"));
	exit(EXIT_SUCCESS);
}

void	philosophy_routine(t_philo *p)
{
	pthread_t	death_checker;

	open_semaphores(p);
	pthread_create(&death_checker, NULL, death_routine, (void *)p);
	while (p->eat_count != 0)
	{
		take_forks(p);
		eating(p);
		sleeping(p);
		message_printer(p, THINKING);
	}
	exit_child(p);
}

/*
** only take forks when both are available!
	the fork_taken variables are shared between philos
**	=> they need to be locked and unlocked when something happens to them
	=> one philo edge case gets handled first => see init
*/

void	take_forks(t_philo *philo)
{
	sem_wait(philo->message_sem);
	if (philo->status == TOOK_FORK)
	{
		message_printer(philo, TOOK_FORK);
		if (countdown(philo, philo->time_to_die))
			return ;
	}
	sem_post(philo->message_sem);
	sem_wait(philo->forks_sem);
	message_printer(philo, TOOK_FORK);
	message_printer(philo, TOOK_FORK);
}

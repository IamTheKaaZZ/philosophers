/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:30 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/23 20:10:22 by bcosters         ###   ########.fr       */
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
	p->death_sem = sem_open(DEATH_SEMA, O_RDWR);
	if (p->death_sem == SEM_FAILED)
		exit(unlink_semaphore(DEATH_SEMA) + 1);
}

void	exit_child(t_philo *p)
{
	if (sem_close(p->message_sem) < 0 || sem_close(p->forks_sem) < 0)
		exit(my_perror("Closing semaphores failure in child.\n"));
	exit(EXIT_SUCCESS);
}

void	philosophy_routine(t_philo *p)
{
	open_semaphores(p);
	while (p->eat_count != 0)
	{
		take_forks(p);
		if (p->status == DEAD || check_death(p))
			exit_child(p);
		eating(p);
		if (p->status == DEAD || check_death(p))
			exit_child(p);
		sleeping(p);
		if (p->status == DEAD || check_death(p))
			exit_child(p);
		p->status = THINKING;
		message_printer(p);
		if (p->status == DEAD || check_death(p))
			exit_child(p);
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
	if (philo->status == TOOK_FORK)
	{
		message_printer(philo);
		if (countdown(philo, philo->new_death_time + 20))
			return ;
	}
	sem_wait(philo->forks_sem);
	if (check_death(philo))
		return ;
	philo->status = TOOK_FORK;
	message_printer(philo);
	message_printer(philo);
}

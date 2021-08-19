/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:30 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/19 18:22:47 by bcosters         ###   ########.fr       */
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
	open_semaphores(p);
	// p->start_time = get_current_time(0);
	while (p->eat_count != 0)
	{
		take_forks(p);
		if (p->status == DEAD)
			exit_child(p);
		eating(p);
		if (p->status == DEAD)
			exit_child(p);
		sleeping(p);
		if (p->status == DEAD)
			exit_child(p);
		p->status = THINKING;
		message_printer(p);
		if (p->status == DEAD)
			exit_child(p);
	}
	exit_child(p);
}

/*
** only take forks when both are available!
	the fork_taken variables are shared between philos
**	=> they need to be locked and unlocked when something happens to them
*/

void	take_forks(t_philo *philo)
{
	t_bool	has_two_forks;

	has_two_forks = FALSE;
	while (!has_two_forks)
	{
		if (check_death(philo))
			return ;
		sem_wait(philo->forks_sem);
		philo->status = TOOK_FORK;
		message_printer(philo);
		sem_wait(philo->forks_sem);
		message_printer(philo);
		has_two_forks = TRUE;
		if (check_death(philo))
			return ;
	}
}

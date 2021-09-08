/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:46:16 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 11:46:17 by bcosters         ###   ########.fr       */
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

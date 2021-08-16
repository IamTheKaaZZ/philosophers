/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/16 15:54:29 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	unlink_semaphore(const char *name)
{
	if (sem_unlink(name) < 0)
		return (my_perror("sem_unlink failure.\n"));
	return (0);
}

void	open_semaphores(t_philo *p)
{
	p->lock_sem = sem_open(LOCK_SEMA, O_RDWR);
	if (p->lock_sem == SEM_FAILED)
		exit(unlink_semaphore(LOCK_SEMA) + 1);
	p->message_sem = sem_open(MESSAGE_SEMA, O_RDWR);
	if (p->lock_sem == SEM_FAILED)
		exit(unlink_semaphore(MESSAGE_SEMA) + 1);
	p->forks_sem = sem_open(FORK_SEMA, O_RDWR);
	if (p->forks_sem == SEM_FAILED)
		exit(unlink_semaphore(FORK_SEMA) + 1);
}

void	philosophy_routine(t_philo *p)
{
	open_semaphores(p);
	while (p->eat_count != 0)
	{
		take_forks(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		eating(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		sleeping(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		p->status = THINKING;
		message_printer(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
	}
	if (sem_close(p->message_sem) < 0 || sem_close(p->lock_sem) < 0
		|| sem_close(p->forks_sem) < 0)
		exit(my_perror("Closing semaphores failure.\n"));
	exit(EXIT_SUCCESS);
}

int	start_processes(t_table *t)
{
	int		i;
	t_ll	start_time;

	start_time = get_current_time(0);
	i = -1;
	while (++i < t->n_philos)
	{
		t->philos[i].id = i;
		t->philos[i].start_time = start_time;
		t->philos[i].pid = fork();
		if (t->philos[i].pid == -1)
			return (my_perror("Forking failure.\n"));
		if (t->philos[i].pid == 0)
			philosophy_routine(&t->philos[i]);
	}
	i = -1;
	while (++i < t->n_philos)
	{
		if (waitpid(t->philos[i].pid, NULL, 0) < 0)
			return (my_perror("Waitpid failure.\n"));
	}
	if (unlink_semaphore(MESSAGE_SEMA) || unlink_semaphore(LOCK_SEMA)
		|| unlink_semaphore(FORK_SEMA))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	t;

	if (error_and_init(&t, argc, argv))
		error_exit(&t, "Data init error.\n", TRUE);
	if (init_semaphores(&t))
		error_exit(&t, "Semaphore init error.\n", TRUE);
	if (init_philos(&t, t.philos, t.n_philos))
		error_exit(&t, "Philosophers init error.\n", TRUE);
	if (start_processes(&t))
		error_exit(&t, "Process forking error.\n", TRUE);
	clear_data(&t);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/17 15:20:41 by bcosters         ###   ########.fr       */
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

int	start_processes(t_table *t)
{
	int		i;
	t_ll	start_time;
	// int		wstatus;

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
	// printf("Starting to wait\n");
	// i = -1;
	// while (TRUE)
	// {
	// 	//0 means all the processes in the group AKA the children
	// 	if (waitpid(0, &wstatus, WNOHANG) < 0)
	// 		return (my_perror("Waitpid failure.\n"));
	// 	if (WIFEXITED(wstatus))
	// 		break ;
	// }
	// printf("killing children\n");
	// i = -1;
	// while (++i < t->n_philos)
	// 	kill(t->philos[i].pid, SIGTERM);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	t;
	int		i;
	int		wstatus;

	if (error_and_init(&t, argc, argv))
		error_exit(&t, "Data init error.\n", TRUE);
	if (init_semaphores(&t))
		error_exit(&t, "Semaphore init error.\n", TRUE);
	if (init_philos(&t, t.philos, t.n_philos))
		error_exit(&t, "Philosophers init error.\n", TRUE);
	if (start_processes(&t))
		error_exit(&t, "Process forking error.\n", TRUE);
	printf("Starting to wait\n");
	while (TRUE)
	{
		//0 means all the processes in the group AKA the children
		if (waitpid(0, &wstatus, WNOHANG) < 0)
			error_exit(&t, "Waitpid failure.\n", TRUE);
		if (WIFEXITED(wstatus))
			break ;
	}
	printf("killing children\n");
	i = -1;
	while (++i < t.n_philos)
		kill(t.philos[i].pid, SIGTERM);
	clear_data(&t);
	exit(EXIT_SUCCESS);
}

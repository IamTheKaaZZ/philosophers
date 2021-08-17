/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/17 20:04:29 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	wait_and_kill(t_table *t)
{
	int		wstatus;
	int		i;
	// t_ll	start_time;

	printf("Starting to wait\n");
	while (TRUE)
	{
		//0 means all the processes in the group AKA the children
		if (waitpid(0, &wstatus, WNOHANG) < 0)
			return (my_perror("Waitpid failure.\n"));
		if (WIFEXITED(wstatus))
			break ;
	}
	printf("killing children\n");
	i = -1;
	while (++i < t->n_philos)
		kill(t->philos[i].pid, SIGTERM);
	return (0);
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
	// start_time = get_current_time(start_time);
	// printf("releasing the sync semaphore at %lld\n", start_time);
	// i = -1;
	// while (++i < t->n_philos)
	// 	t->philos[i].start_time = start_time;
	// sem_post(t->sync_sema);
	return (wait_and_kill(t));
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

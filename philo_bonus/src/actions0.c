/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:30 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/17 15:21:07 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// void	exit_child(t_philo *p)
// {
// 	if (sem_close(p->message_sem) < 0 || sem_close(p->forks_sem) < 0)
// 		exit(my_perror("Closing semaphores failure in child.\n"));
// 	exit(EXIT_SUCCESS);
// }

// t_bool	wait_and_kill(t_table *t)
// {
// 	int	i;
// 	int	wstatus;

// 	printf("Starting to wait\n");
// 	while (TRUE)
// 	{
// 		//0 means all the processes in the group AKA the children
// 		if (waitpid(0, &wstatus, WNOHANG) < 0)
// 			return (my_perror("Waitpid failure.\n"));
// 		if (WIFEXITED(wstatus))
// 			break ;
// 	}
// 	printf("killing children\n");
// 	i = -1;
// 	while (++i < t->n_philos)
// 		kill(t->philos[i].pid, SIGTERM);
// 	return (0);
// }

/*
** only take forks when both are available!
	the fork_taken variables are shared between philos
**	=> they need to be locked and unlocked when something happens to them
*/

void	take_forks(t_philo *philo)
{
	int		i;
	t_bool	has_two_forks;

	has_two_forks = FALSE;
	while (!has_two_forks)
	{
		i = 0;
		while (i < 2)
		{
			if (check_death(philo))
				return ;
			if (sem_wait(philo->forks_sem) < 0)
				continue ;
			i++;
		}
		if (i == 2)
			has_two_forks = TRUE;
		if (check_death(philo))
			return ;
	}
	philo->status = TOOK_FORK;
	message_printer(philo);
	message_printer(philo);
}

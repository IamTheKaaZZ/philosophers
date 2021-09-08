/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:00:59 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 15:17:38 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	clear_data(t_table *t)
{
	int	i;

	if (t->philos)
	{
		i = -1;
		while (++i < t->n_philos)
		{
			sem_close(t->philos[i].time_sem);
			sem_unlink(t->philos[i].sema_name);
			free(t->philos[i].sema_name);
		}
		free(t->philos);
		t->philos = NULL;
	}
	sem_close(t->full_sem);
	sem_close(t->end_sem);
	sem_unlink(END_SEMA);
	sem_unlink(FULL_SEMA);
	sem_unlink(MESSAGE_SEMA);
	sem_unlink(FORK_SEMA);
}

int	my_perror(const char *str)
{
	if (str)
		printf("ERROR: %s", str);
	return (EXIT_FAILURE);
}

int	error_exit(t_table *t, char *errmessage, t_bool clear)
{
	if (clear == TRUE)
		clear_data(t);
	exit(my_perror(errmessage));
}

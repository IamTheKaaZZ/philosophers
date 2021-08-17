/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:00:59 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/17 18:36:09 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	clear_data(t_table *t)
{
	int	i;

	if (t->philos)
	{
		free(t->philos);
		t->philos = NULL;
	}
	if (t->sync_semas)
	{
		i = -1;
		while (++i < t->n_philos)
		{
			if (sem_close(t->sync_semas[i]) < 0)
				sem_unlink(SYNC_SEMA);
		}
		free(t->sync_semas);
		t->sync_semas = NULL;
	}
	sem_unlink(MESSAGE_SEMA);
	sem_unlink(FORK_SEMA);
	sem_unlink(SYNC_SEMA);
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

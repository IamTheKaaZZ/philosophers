/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:00:59 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/16 11:57:36 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	clear_data(t_table *t)
{
	int	i;

	// if (t->taken_forks)
	// 	free(t->taken_forks);
	// if (t->forks_mutex)
	// {
	// 	i = -1;
	// 	while (++i < t->n_philos)
	// 		pthread_mutex_destroy(&t->forks_mutex[i]);
	// 	free(t->forks_mutex);
	// 	t->forks_mutex = NULL;
	// }
	if (t->philos)
	{
		free(t->philos);
		t->philos = NULL;
	}
	pthread_mutex_destroy(&t->message_mutex);
}

static int	my_perror(const char *str)
{
	if (str)
		printf("ERROR: %s", str);
	return (1);
}

int	error_exit(t_table *t, char *errmessage, t_bool clear)
{
	if (clear == TRUE)
		clear_data(t);
	return (my_perror(errmessage));
}
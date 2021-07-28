/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:00:59 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/28 12:16:46 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	clear_data(t_data *d)
{
	int	i;

	if (d->forks_mutex)
	{
		i = -1;
		while (++i < d->n_philos)
			pthread_mutex_destroy(&d->forks_mutex[i]);
		free(d->forks_mutex);
		d->forks_mutex = NULL;
	}
	if (d->philos)
	{
		i = -1;
		while (++i < d->n_philos)
		{
			pthread_mutex_destroy(&d->philos[i].eating_mutex);
			pthread_mutex_destroy(&d->philos[i].philo_mutex);
		}
		free(d->philos);
		d->philos = NULL;
	}
	pthread_mutex_destroy(&d->dead_mutex);
	pthread_mutex_destroy(&d->message_mutex);
}

static int	my_perror(const char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (1);
}

int	error_exit(t_data *d, char *errmessage, t_bool clear)
{
	if (clear == TRUE)
		clear_data(d);
	return (my_perror(errmessage));
}

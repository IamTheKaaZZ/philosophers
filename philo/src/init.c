/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:22:16 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/28 12:24:30 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_bool	init_struct(t_data *d, int argc, char **argv)
{
	d->n_philos = (long)ft_atoi(argv[1]);
	d->death_time = (long)ft_atoi(argv[2]);
	d->eat_time = (long)ft_atoi(argv[3]);
	d->sleep_time = (long)ft_atoi(argv[4]);
	if (d->n_philos < 2 || d->n_philos > 200)
		return (1);
	if (d->death_time < 60)
		return (1);
	if (d->eat_time < 60)
		return (1);
	if (d->sleep_time < 60)
		return (1);
	if (argc == 6)
	{
		d->max_eat = (long)ft_atoi(argv[5]);
		if (d->max_eat < 0)
			return (1);
	}
	else
		d->max_eat = -1;
	d->philos = NULL;
	d->forks_mutex = NULL;
	return (0);
}

t_bool	error_and_init(t_data *d, int argc, char **argv)
{
	if (argc != 6)
	{
		if (argc < 5)
		{
			write(2, "Not enough arguments.\n", 23);
			return (1);
		}
		else if (argc > 6)
		{
			write(2, "Too many arguments.\n", 21);
			return (1);
		}
	}
	if (init_struct(d, argc, argv))
		return (1);
	d->philos = (t_philo *)malloc(d->n_philos * sizeof(t_philo));
	if (!d->philos)
		return (1);
	return (0);
}

void	init_philos(t_philo *philos, int n_philos)
{
	int	i;

	i = -1;
	while (++i < n_philos)
	{
		philos[i].position = i;
		philos[i].left_fork = i;
		if (philos[i].left_fork = n_philos - 1)
			philos[i].right_fork = 0;
		else
			philos[i].right_fork = i + 1;
		philos[i].eat_count = 0;
		philos[i].has_forks = FALSE;
		philos[i].is_eating = FALSE;
		philos[i].is_asleep = FALSE;
		philos[i].is_thinking = FALSE;
		philos[i].is_dead = FALSE;
		philos[i].time_since_eat = 0;
		pthread_mutex_init(&philos[i].philo_mutex, NULL);
		pthread_mutex_init(&philos[i].eating_mutex, NULL);
		pthread_mutex_lock(&philos[i].eating_mutex);
	}
}

t_bool	init_mutexes(t_data	*d)
{
	int	i;

	pthread_mutex_init(&d->message_mutex, NULL);
	pthread_mutex_init(&d->dead_mutex, NULL);
	pthread_mutex_lock(&d->dead_mutex);
	d->forks_mutex =
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * d->n_philos);
	if (!d->forks_mutex)
		return (1);
	i = -1;
	while (++i < d->n_philos)
		pthread_mutex_init(&d->forks_mutex[i], NULL);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:22:16 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/29 11:42:28 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_bool	setup_table(t_table *t, int argc, char **argv)
{
	t->n_philos = (long)ft_atoi(argv[1]);
	t->death_time = (long)ft_atoi(argv[2]);
	t->eat_time = (long)ft_atoi(argv[3]);
	t->sleep_time = (long)ft_atoi(argv[4]);
	if (t->n_philos < 2 || t->n_philos > 200)
		return (1);
	if (t->death_time < 60)
		return (1);
	if (t->eat_time < 60)
		return (1);
	if (t->sleep_time < 60)
		return (1);
	if (argc == 6)
	{
		t->max_eat = (long)ft_atoi(argv[5]);
		if (t->max_eat < 0)
			return (1);
	}
	else
		t->max_eat = -1;
	t->philos = NULL;
	t->forks_mutex = NULL;
	return (0);
}

t_bool	error_and_init(t_table *t, int argc, char **argv)
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
	if (setup_table(t, argc, argv))
		return (1);
	t->philos = (t_philo *)malloc(t->n_philos * sizeof(t_philo));
	if (!t->philos)
		return (1);
	return (0);
}

void	init_philos(t_table *t, t_philo *philos, int n_philos)
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
		philos[i].status = THINKING;
		philos[i].time_to_die = t->death_time;
		philos[i].time_since_eat = 0;
		philos[i].new_death_time = 0;
		pthread_mutex_init(&philos[i].philo_mutex, NULL);
		pthread_mutex_init(&philos[i].eating_mutex, NULL);
		pthread_mutex_lock(&philos[i].eating_mutex);
	}
}

t_bool	init_mutexes(t_table	*t)
{
	int	i;

	pthread_mutex_init(&t->message_mutex, NULL);
	pthread_mutex_init(&t->dead_mutex, NULL);
	pthread_mutex_lock(&t->dead_mutex);
	t->forks_mutex =
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * t->n_philos);
	if (!t->forks_mutex)
		return (1);
	i = -1;
	while (++i < t->n_philos)
		pthread_mutex_init(&t->forks_mutex[i], NULL);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:22:16 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/10 14:24:24 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_bool	setup_table(t_table *t, int argc, char **argv)
{
	memset(t, 0, sizeof(t_table));
	t->n_philos = ft_atoi(argv[1]);
	t->death_time = ft_atoi(argv[2]);
	t->eat_time = ft_atoi(argv[3]);
	t->sleep_time = ft_atoi(argv[4]);
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
		t->max_eat = ft_atoi(argv[5]);
		if (t->max_eat < 0)
			return (1);
	}
	else
		t->max_eat = -1;
	return (0);
}

t_bool	error_and_init(t_table *t, int argc, char **argv)
{
	if (argc != 6)
	{
		if (argc < 5)
		{
			printf("Not enough arguments.\n");
			return (1);
		}
		else if (argc > 6)
		{
			printf("Too many arguments.\n");
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
		philos[i].id = i;
		philos[i].eat_count = 0;
		philos[i].status = THINKING;
		philos[i].time_to_eat = t->eat_time;
		philos[i].time_to_sleep = t->sleep_time;
		philos[i].time_to_die = t->death_time;
		philos[i].time_ate = 0;
		philos[i].new_death_time = t->death_time;
		philos[i].left_fork_taken = &t->taken_forks[i];
		philos[i].left_fork_m = &t->forks_mutex[i];
		if (i == n_philos - 1)
		{
			philos[i].right_fork_taken = &t->taken_forks[0];
			philos[i].right_fork_m = &t->forks_mutex[0];
		}
		else
		{
			philos[i].right_fork_taken = &t->taken_forks[i + 1];
			philos[i].right_fork_m = &t->forks_mutex[i + 1];
		}
		philos[i].message_m = &t->message_mutex;
		pthread_mutex_init(&philos[i].philo_mutex, NULL);
	}
}

t_bool	init_mutexes(t_table *t)
{
	int	i;

	pthread_mutex_init(&t->message_mutex, NULL);
	t->forks_mutex =
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * t->n_philos);
	if (!t->forks_mutex)
		return (1);
	i = -1;
	while (++i < t->n_philos)
	{
		if (pthread_mutex_init(&t->forks_mutex[i], NULL) != 0)
			printf("error in initialization of fork mutexes %d\n", i);
	}
	t->taken_forks = (t_bool *)malloc(sizeof(t_bool) * t->n_philos);
	if (!t->taken_forks)
		return (1);
	memset(t->taken_forks, FALSE, sizeof(t_bool) * t->n_philos);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/28 11:20:39 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	neg_check(t_data *d)
{
	if (d->n_philos < 2 || d->n_philos > 200)
		return (1);
	if (d->death_time < 60)
		return (1);
	if (d->eat_time < 60)
		return (1);
	if (d->sleep_time < 60)
		return (1);
	return (0);
}

t_bool	init_struct(t_data *d, int argc, char **argv)
{
	d->n_philos = (long)ft_atoi(argv[1]);
	d->death_time = (long)ft_atoi(argv[2]);
	d->eat_time = (long)ft_atoi(argv[3]);
	d->sleep_time = (long)ft_atoi(argv[4]);
	if (neg_check(d))
		return (1);
	if (argc == 6)
	{
		d->max_eat = (long)ft_atoi(argv[5]);
		if (d->max_eat < 0)
		{
			write(2, "You forgetti about the spaghetti, many regretti.\n", 50);
			return (1);
		}
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;
	int		i;

	if (error_and_init(&d, argc, argv))
		return (1);
	d.threads = (pthread_t *)malloc(d.n_philos * sizeof(pthread_t));
	if (!d.threads)
		return (1);
	i = -1;
	while (++i < d.n_philos)
	{
		if (pthread_create(&d.threads[i], NULL, philosophy, args) == -1)
		{
			free(d.threads);
			return (1);
		}
	}
	i = -1;
	while (++i < d.n_philos)
	{
		if (pthread_join(d.threads[i], NULL) == -1)
		{
			free(d.threads);
			return (1);
		}
	}
	return (0);
}

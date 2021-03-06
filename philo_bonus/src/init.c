/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:22:16 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 15:27:46 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static t_bool	setup_table(t_table *t, int argc, char **argv)
{
	memset(t, 0, sizeof(t_table));
	t->n_philos = ft_atoi(argv[1]);
	t->death_time = ft_atoi(argv[2]);
	t->eat_time = ft_atoi(argv[3]);
	t->sleep_time = ft_atoi(argv[4]);
	if (t->n_philos < 1 || t->n_philos > 200)
		return (my_perror("Too little or too many Philosophers.\n"));
	if (t->death_time <= 0)
		return (my_perror("(Death time <= 0) No immortality.\n"));
	if (t->eat_time <= 0)
		return (my_perror("(Eat time <= 0) No time travelling.\n"));
	if (t->sleep_time <= 0)
		return (my_perror("(Sleep time <= 0) Philosopher != Student.\n"));
	if (argc == 6)
	{
		t->max_eat = ft_atoi(argv[5]);
		if (t->max_eat <= 0)
			return (my_perror("(Must eat <= 0) (┛ಠ_ಠ)┛彡┻━┻ No spaghetti.\n"));
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
			return (my_perror("Not enough arguments.\n"));
		else if (argc > 6)
			return (my_perror("Too many arguments.\n"));
	}
	if (setup_table(t, argc, argv))
		return (my_perror("Given arguments are invalid.\n"));
	t->philos = (t_philo *)malloc(t->n_philos * sizeof(t_philo));
	if (!t->philos)
		return (my_perror("Malloc fail.\n"));
	return (0);
}

char	*make_named_sema(char const *prefix, int id)
{
	int		i;
	char	*result;
	int		num_count;

	i = id;
	num_count = 0;
	while (i)
	{
		i /= 10;
		num_count++;
	}
	result = malloc((num_count + ft_strlen(prefix) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (prefix[++i])
		result[i] = prefix[i];
	while (id > 0)
	{
		result[i++] = (id % 10) + '0';
		id /= 10;
	}
	result[i] = 0;
	return (result);
}

/*
	No longer need the status to check death or end.
*/

t_bool	init_philos(t_table *t, t_philo *philos, int n_philos)
{
	int		i;

	i = -1;
	while (++i < n_philos)
	{
		philos[i].id = i;
		philos[i].eat_count = t->max_eat;
		philos[i].start_time = 0;
		philos[i].time_to_eat = t->eat_time;
		philos[i].time_to_sleep = t->sleep_time;
		philos[i].time_to_die = t->death_time;
		philos[i].time_ate = 0;
		philos[i].sema_name = make_named_sema(TIME_SEMA, i);
		sem_unlink(philos[i].sema_name);
		if (sem_open_check(&philos[i].time_sem, philos[i].sema_name, 1))
			return (1);
	}
	return (0);
}

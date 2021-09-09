/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/09 13:45:47 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_routine(void *philo)
{
	t_philo	*p;
	t_bool	end;

	end = FALSE;
	p = (t_philo *)philo;
	while (!end)
	{
		pthread_mutex_lock(&p->check_m);
		if (p->eat_count == 0 || check_death(p))
			end = TRUE;
		pthread_mutex_unlock(&p->check_m);
		usleep(1000);
	}
	return (NULL);
}

void	*philosophy_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->eat_count != 0 && p->status != DEAD)
	{
		take_forks(p);
		eating(p);
		sleeping(p);
		message_printer(p, THINKING);
	}
	return (NULL);
}

int	start_threads(t_table *t)
{
	int			i;
	t_ll		start_time;
	pthread_t	death;

	start_time = get_current_time(0);
	i = -1;
	while (++i < t->n_philos)
	{
		t->philos[i].id = i;
		t->philos[i].start_time = start_time;
		if (pthread_create(&t->philos[i].thread,
				NULL,
				philosophy_routine,
				(void *)&t->philos[i])
			!= 0)
			return (1);
		if (pthread_create(&death, NULL, death_routine,
				(void *)&t->philos[i]) != 0)
			return (1);
		pthread_detach(death);
	}
	i = -1;
	while (++i < t->n_philos)
		pthread_join(t->philos[i].thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	t;

	if (error_and_init(&t, argc, argv))
		return (error_exit(&t, "Data init error.\n", TRUE));
	if (init_mutexes(&t))
		return (error_exit(&t, "Mutex init error.\n", TRUE));
	if (init_philos(&t, t.philos, t.n_philos))
		return (error_exit(&t, "Philosophers init error.\n", TRUE));
	if (start_threads(&t))
		return (error_exit(&t, "Thread creation error.\n", TRUE));
	clear_data(&t);
	return (0);
}

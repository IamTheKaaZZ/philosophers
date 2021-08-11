/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/11 12:55:23 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophy_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->eat_count != 0)
	{
		take_forks(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		eating(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		sleeping(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		p->status = THINKING;
		message_printer(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
	}
	return (NULL);
}

int	start_threads(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_philos)
	{
		t->philos[i].id = i;
		if (pthread_create(&t->philos[i].thread,
				NULL,
				philosophy_routine,
				(void *)&t->philos[i])
				!= 0)
			return (1);
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
	init_philos(&t, t.philos, t.n_philos);
	if (start_threads(&t))
		return (error_exit(&t, "Thread error.\n", TRUE));
	//main thread should check for deaths and if they are all full
	// if (death_end_tracker(&t))
	// {
	// 	clear_data(&t);
	// 	return (0);
	// }
	clear_data(&t);
	return (0);
}

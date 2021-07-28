/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/28 12:25:02 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	d;
	int		i;

	if (error_and_init(&d, argc, argv))
		return (error_exit(&d, "Data init error.\n", TRUE));
	init_philos(d.philos, d.n_philos);
	if (init_mutexes)
		return (error_exit(&d, "Mutex init error.\n", TRUE));
	i = -1;
	while (++i < d.n_philos)
	{
		if (pthread_create(&d.philos[i].thread, NULL, philosophy, args) == -1)
		{
			free(d.philos);
			return (1);
		}
	}
	i = -1;
	while (++i < d.n_philos)
	{
		if (pthread_join(d.philos[i].thread, NULL) == -1)
		{
			free(d.philos);
			return (1);
		}
	}
	return (0);
}

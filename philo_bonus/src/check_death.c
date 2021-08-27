/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:08:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/27 11:17:44 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_bool	check_death(t_philo *p)
{
	t_ll	curr_time;

	sem_wait(p->time_sem);
	curr_time = get_current_time(p->start_time);
	if (curr_time >= p->time_ate + p->time_to_die)
	{
		message_printer(p, DEAD);
		return (TRUE);
	}
	sem_post(p->time_sem);
	return (FALSE);
}

void	*death_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (TRUE)
	{
		if (check_death(philo))
		{
			kill(0, SIGINT);
			break ;
		}
		usleep(ONE_MS);
	}
	return (NULL);
}

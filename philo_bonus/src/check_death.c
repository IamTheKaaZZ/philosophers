/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:08:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/24 16:11:30 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_bool	check_death(t_philo *p)
{
	if (get_current_time(p->start_time) >= p->time_ate + p->time_to_die)
	{
		message_printer(p, DEAD);
		return (TRUE);
	}
	return (FALSE);
}

void	*death_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (TRUE)
	{
		sem_wait(philo->message_sem);
		if (philo->eat_count == 0 || check_death(philo))
		{
			kill(0, SIGINT);
			break ;
		}
		sem_post(philo->message_sem);
		usleep(ONE_MS);
	}
	return (NULL);
}

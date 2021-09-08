/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:08:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 11:50:48 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_bool	check_death(t_philo *p)
{
	t_ll	curr_time;

	curr_time = get_current_time(p->start_time);
	if (curr_time >= p->time_ate + p->time_to_die && p->eat_count != 0)
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
		sem_wait(philo->time_sem);
		if (check_death(philo) || philo->eat_count == 0)
		{
			kill(0, SIGINT);
			break ;
		}
		sem_post(philo->time_sem);
	}
	return (NULL);
}

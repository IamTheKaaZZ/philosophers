/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:08:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/24 11:22:51 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_bool	check_death(t_philo *p)
{
	if (get_current_time(p->start_time) >= p->time_ate + p->time_to_die)
	{
		p->status = DEAD;
		message_printer(p);
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
		if (check_death(philo))
			return (NULL);
		sem_post(philo->message_sem);
		usleep(ONE_MS);
	}
	return (NULL);
}

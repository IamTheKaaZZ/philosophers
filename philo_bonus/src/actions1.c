/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:24:10 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/24 14:29:43 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_bool	countdown(t_philo *philo, t_ll end_time)
{
	while (get_current_time(philo->start_time) < end_time)
	{
		usleep(100);
		if (get_current_time(philo->start_time) >= end_time)
			break ;
	}
	return (0);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->message_sem);
	message_printer(philo, EATING);
	philo->time_ate = get_current_time(philo->start_time);
	sem_post(philo->message_sem);
	philo->eat_count--;
	if (countdown(philo, philo->time_ate + philo->time_to_eat))
		return ;
}

/*
**	The current philosopher drops their forks and falls asleep
**	=> protect the fork state with the mutexes
*/

void	sleeping(t_philo *philo)
{
	t_ll	end_sleep;

	message_printer(philo, SLEEPING);
	sem_post(philo->forks_sem);
	end_sleep = get_current_time(philo->start_time) + philo->time_to_sleep;
	if (countdown(philo, end_sleep))
		return ;
}

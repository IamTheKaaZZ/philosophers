/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:24:10 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/27 11:18:49 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_bool	countdown(t_philo *philo, t_ll end_time)
{
	t_ll	curr_time;

	curr_time = get_current_time(philo->start_time);
	while (curr_time < end_time)
	{
		usleep(100);
		curr_time = get_current_time(philo->start_time);
		if (curr_time >= end_time)
			break ;
	}
	return (0);
}

void	eating(t_philo *philo)
{
	message_printer(philo, EATING);
	sem_wait(philo->time_sem);
	philo->time_ate = get_current_time(philo->start_time);
	philo->eat_count--;
	sem_post(philo->time_sem);
	usleep(philo->time_to_eat);
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
	usleep(philo->time_to_sleep);
	end_sleep = get_current_time(philo->start_time) + philo->time_to_sleep;
	if (countdown(philo, end_sleep))
		return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:45:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 11:45:55 by bcosters         ###   ########.fr       */
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

/*
** only take forks when both are available!
	the fork_taken variables are shared between philos
**	=> they need to be locked and unlocked when something happens to them
	=> one philo edge case gets handled first => only 1 fork so the philo waits
*/

void	take_forks(t_philo *philo)
{
	sem_wait(philo->forks_sem);
	message_printer(philo, TOOK_FORK);
	sem_wait(philo->forks_sem);
	message_printer(philo, TOOK_FORK);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->time_sem);
	message_printer(philo, EATING);
	philo->time_ate = get_current_time(philo->start_time);
	philo->eat_count--;
	usleep(philo->time_to_eat);
	if (countdown(philo, philo->time_ate + philo->time_to_eat))
		return ;
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
	sem_post(philo->time_sem);
}

/*
**	The current philosopher drops their forks and falls asleep
**	=> protect the fork state with the mutexes
*/

void	sleeping(t_philo *philo)
{
	t_ll	end_sleep;

	message_printer(philo, SLEEPING);
	usleep(philo->time_to_sleep);
	end_sleep = get_current_time(philo->start_time) + philo->time_to_sleep;
	if (countdown(philo, end_sleep))
		return ;
}

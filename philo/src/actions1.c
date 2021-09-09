/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:24:10 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/09 13:42:29 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	countdown(t_philo *philo, t_ll end_time)
{
	t_ll	curr_time;

	curr_time = get_current_time(philo->start_time);
	while (curr_time < end_time)
	{
		usleep(10);
		curr_time = get_current_time(philo->start_time);
		if (curr_time >= end_time)
			break ;
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->check_m);
	message_printer(philo, EATING);
	philo->time_ate = get_current_time(philo->start_time);
	philo->eat_count--;
	usleep(philo->time_to_eat);
	countdown(philo, philo->time_ate + philo->time_to_eat);
	put_fork_down(philo->right_fork_m, philo->right_fork_taken);
	put_fork_down(philo->left_fork_m, philo->left_fork_taken);
	pthread_mutex_unlock(&philo->check_m);
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
	countdown(philo, end_sleep);
}

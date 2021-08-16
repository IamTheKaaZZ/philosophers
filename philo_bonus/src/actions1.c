/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:24:10 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/16 17:01:30 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static t_bool	countdown(t_philo *philo, t_ll end_time)
{
	while (get_current_time(philo->start_time) < end_time)
	{
		if (check_death(philo))
			return (1);
		usleep(100);
		if (get_current_time(philo->start_time) >= end_time)
			break ;
	}
	return (0);
}

void	eating(t_philo *philo)
{
	t_ll	start_eat;
	t_ll	end_eat;

	philo->status = EATING;
	message_printer(philo);
	start_eat = get_current_time(philo->start_time);
	end_eat = start_eat + philo->time_to_eat;
	philo->new_death_time = start_eat + philo->time_to_die;
	philo->eat_count--;
	if (countdown(philo, end_eat))
		return ;
}

/*
**	The current philosopher drops their forks and falls asleep
**	=> protect the fork state with the mutexes
*/

void	sleeping(t_philo *philo)
{
	t_ll	end_sleep;

	philo->status = SLEEPING;
	message_printer(philo);
	sem_wait(philo->lock_sem);
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
	sem_post(philo->lock_sem);
	// put_fork_down(philo->left_fork_m, philo->left_fork_taken);
	// put_fork_down(philo->right_fork_m, philo->right_fork_taken);
	end_sleep = get_current_time(philo->start_time) + philo->time_to_sleep;
	if (countdown(philo, end_sleep))
		return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:30 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/10 15:43:36 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_bool	check_death(t_philo *p)
{
		pthread_mutex_lock(&p->philo_mutex);
		if (p->status != EATING && get_current_time() > p->new_death_time)
		{
			p->status = DEAD;
			message_printer(p);
			pthread_mutex_unlock(&p->philo_mutex);
			return(TRUE);
		}
		pthread_mutex_unlock(&p->philo_mutex);
		return(FALSE);
}

/*
** only take forks when both are available!
**	the fork_taken variables are shared between philos
**	=> they need to be locked and unlocked when something happens to them
*/

void	take_forks(t_philo *philo)
{
	t_bool	locked;

	locked = FALSE;
	while (!locked)
	{
		pthread_mutex_lock(philo->left_fork_m);
		pthread_mutex_lock(philo->right_fork_m);
		if (*philo->left_fork_taken == FALSE
			&& *philo->right_fork_taken == FALSE)
		{
			*philo->left_fork_taken = TRUE;
			*philo->right_fork_taken = TRUE;
			locked = TRUE;
		}
		pthread_mutex_unlock(philo->left_fork_m);
		pthread_mutex_unlock(philo->right_fork_m);
		if (locked)
		{
			philo->status = TOOK_FORK;
			message_printer(philo);
			message_printer(philo);
		}
		else
		{
			if (check_death(philo))
				return ;
		}
	}
}

void	eating(t_philo *philo)
{
	philo->status = EATING;
	message_printer(philo);
	usleep(philo->time_to_eat * ONE_MS);
	philo->time_ate = get_current_time();
	philo->new_death_time =
		philo->time_ate + philo->time_to_die;
	philo->eat_count++;
}

/*
**	The current philosopher drops their forks and falls asleep
**	=> protect the fork state with the mutexes
*/

void	sleeping(t_philo *philo)
{
	t_ll	sleeptime;

	sleeptime = philo->time_to_sleep * ONE_MS;
	philo->status = SLEEPING;
	message_printer(philo);
	pthread_mutex_lock(philo->left_fork_m);
	pthread_mutex_lock(philo->right_fork_m);
	*philo->left_fork_taken = FALSE;
	*philo->right_fork_taken = FALSE;
	pthread_mutex_unlock(philo->left_fork_m);
	pthread_mutex_unlock(philo->right_fork_m);
	while (sleeptime)
	{
		if (check_death(philo))
			return ;
		usleep(100);
		sleeptime -= 100;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:30 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/09 13:39:24 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_bool	one_philo_case(t_philo *philo)
{
	if (philo->left_fork_m == philo->right_fork_m)
	{
		message_printer(philo, TOOK_FORK);
		while (TRUE)
		{
			if (check_death(philo))
				return (TRUE);
		}
	}
	return (FALSE);
}

static t_bool	take_one_fork(pthread_mutex_t *fork, t_bool *taken)
{
	t_bool	success;

	success = FALSE;
	pthread_mutex_lock(fork);
	if (*taken == FALSE)
	{
		*taken = TRUE;
		success = TRUE;
	}
	pthread_mutex_unlock(fork);
	return (success);
}

void	put_fork_down(pthread_mutex_t *fork, t_bool *taken)
{
	pthread_mutex_lock(fork);
	*taken = FALSE;
	pthread_mutex_unlock(fork);
}

static t_bool	check_available_forks(t_philo *philo)
{
	if (take_one_fork(philo->right_fork_m, philo->right_fork_taken))
	{
		if (take_one_fork(philo->left_fork_m, philo->left_fork_taken))
			return (TRUE);
		else
			put_fork_down(philo->right_fork_m, philo->right_fork_taken);
	}
	return (FALSE);
}

/*
** only take forks when both are available!
	the fork_taken variables are shared between philos
**	=> they need to be locked and unlocked when something happens to them
*/

void	take_forks(t_philo *philo)
{
	if (one_philo_case(philo))
		return ;
	while (TRUE)
	{
		if (check_available_forks(philo))
		{
			message_printer(philo, TOOK_FORK);
			message_printer(philo, TOOK_FORK);
			return ;
		}
	}
}

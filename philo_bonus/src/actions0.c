/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:30 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/17 13:03:45 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

/*
** only take forks when both are available!
	the fork_taken variables are shared between philos
**	=> they need to be locked and unlocked when something happens to them
*/

void	take_forks(t_philo *philo)
{
	int		i;
	t_bool	has_two_forks;

	has_two_forks = FALSE;
	while (!has_two_forks)
	{
		i = 0;
		while (i < 2)
		{
			if (check_death(philo))
				return ;
			if (sem_wait(philo->forks_sem) < 0)
				continue ;
			i++;
		}
		if (i == 2)
			has_two_forks = TRUE;
		if (check_death(philo))
			return ;
	}
	philo->status = TOOK_FORK;
	message_printer(philo);
	message_printer(philo);
}

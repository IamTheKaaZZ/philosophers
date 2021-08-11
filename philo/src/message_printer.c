/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:29:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/11 12:39:31 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	message_printer(t_philo *philo)
{
	static char	action_str[5][100] = {
		"\033[34mhas taken a fork\033[0m",
		"\033[32;1mis eating\033[0m",
		"\033[35mis sleeping\033[0m",
		"\033[36mis thinking\033[0m",
		"\033[31;1mdied\033[0m"
	};

	pthread_mutex_lock(philo->message_m);
	if (*philo->somebody_is_dead)
		philo->status = DEAD;
	else
	{
		printf("\033[45;1m%lld ms:\033[33;1m Philosoper %d\033[0m %s\n",
			get_time_elapsed(),
			philo->id + 1,
			action_str[philo->status]
			);
	}
	if (philo->status == DEAD && !*philo->somebody_is_dead)
		*philo->somebody_is_dead = TRUE;
	pthread_mutex_unlock(philo->message_m);
}

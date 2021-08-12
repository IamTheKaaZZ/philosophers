/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:29:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/12 14:11:57 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	message_printer(t_philo *philo)
{
	static char	action_str[5][100] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	pthread_mutex_lock(philo->message_m);
	if (*philo->somebody_is_dead)
		philo->status = DEAD;
	else
	{
		printf("%lld %d %s\n",
			get_current_time(philo->start_time),
			philo->id + 1,
			action_str[philo->status]
			);
	}
	if (philo->status == DEAD && !*philo->somebody_is_dead)
		*philo->somebody_is_dead = TRUE;
	pthread_mutex_unlock(philo->message_m);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:29:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/08 17:51:36 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	message_printer(t_philo *philo, int status)
{
	static char	action_str[5][100] = {
		"\033[32mhas taken a fork.\033[0m",
		"\033[36mis eating.\033[0m",
		"\033[34;1mis sleeping.\033[0m",
		"\033[35mis thinking.\033[0m",
		"\033[31;1mdied.\033[0m"
	};

	pthread_mutex_lock(philo->message_m);
	if (*philo->somebody_is_dead)
		philo->status = DEAD;
	else
	{
		printf("\033[46;1m[%lld ms] \033[33mPhilosopher %d\033[0m %s\n",
			get_current_time(philo->start_time),
			philo->id + 1,
			action_str[status]
			);
	}
	if (status == DEAD && !*philo->somebody_is_dead)
	{
		*philo->somebody_is_dead = TRUE;
		philo->status = DEAD;
	}
	pthread_mutex_unlock(philo->message_m);
}

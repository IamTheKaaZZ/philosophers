/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:29:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/16 15:38:15 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	message_printer(t_philo *philo)
{
	static char	action_str[5][100] = {
		"\033[32mhas taken a fork from the middle.\033[0m",
		"\033[36mis eating.\033[0m",
		"\033[34;1mis sleeping.\033[0m",
		"\033[35mis thinking.\033[0m",
		"\033[31;1mdied.\033[0m"
	};

	sem_wait(philo->message_sem);
	if (*philo->somebody_is_dead)
		philo->status = DEAD;
	else
	{
		printf("\033[46;1m[%lld ms] \033[33mPhilosopher %d\033[0m %s\n",
			get_current_time(philo->start_time),
			philo->id + 1,
			action_str[philo->status]
			);
	}
	if (philo->status == DEAD && !*philo->somebody_is_dead)
		*philo->somebody_is_dead = TRUE;
	sem_post(philo->message_sem);
}

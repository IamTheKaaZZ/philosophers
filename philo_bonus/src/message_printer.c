/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:29:54 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/27 11:17:34 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

/*
	Replaced the mutex with a semaphore
	+ force other philos to wait until they get killed by the parent
		-> sem_wait locks them into waiting forever after someone died
		-> The dead philosopher will get detected by waitpid in the parent
		-> The parent then kills all remaining waitng processes
*/

void	message_printer(t_philo *philo, int status)
{
	static char	action_str[5][100] = {
		"\033[32mhas taken a fork from the middle.\033[0m",
		"\033[36mis eating.\033[0m",
		"\033[34;1mis sleeping.\033[0m",
		"\033[35mis thinking.\033[0m",
		"\033[31;1mdied.\033[0m"
	};

	sem_wait(philo->message_sem);
	printf("\033[46;1m[%lld ms] \033[33mPhilosopher %d\033[0m %s\n",
		get_current_time(philo->start_time),
		philo->id + 1,
		action_str[status]
		);
	sem_post(philo->message_sem);
}

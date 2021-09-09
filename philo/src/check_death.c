/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:08:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/09/09 13:27:18 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_bool	check_death(t_philo *p)
{
	t_ll	curr_time;

	curr_time = get_current_time(p->start_time);
	if (curr_time >= p->time_ate + p->time_to_die && p->eat_count != 0)
	{
		message_printer(p, DEAD);
		return (TRUE);
	}
	return (FALSE);
}

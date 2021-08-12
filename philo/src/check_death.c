/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 11:08:45 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/12 14:57:10 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_bool	check_death(t_philo *p)
{
	if (get_current_time(p->start_time) >= p->new_death_time)
	{
		p->status = DEAD;
		message_printer(p);
		return (TRUE);
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_elapsed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:40:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/12 15:44:38 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_ll	get_time_elapsed(void)
{
	static struct timeval	tv;
	static time_t			start_sec;
	static suseconds_t		start_usec;

	gettimeofday(&tv, NULL);
	if (!start_sec)
	{
		start_sec = tv.tv_sec;
		start_usec = tv.tv_usec;
	}
	return ((tv.tv_sec - start_sec) * 1000LL
		+ (tv.tv_usec - start_usec) / 1000);
}

t_ll	get_current_time(t_ll start_time)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL + tv.tv_usec / 1000) - start_time);
}

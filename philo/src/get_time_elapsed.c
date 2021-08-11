/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_elapsed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:40:05 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/11 15:01:16 by bcosters         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:24:12 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/19 13:29:39 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

typedef unsigned int	t_ui;
typedef int				t_bool;
typedef struct s_philo
{
	t_ui	n_philos;
	t_ui	death_time;
	t_ui	eat_time;
	t_ui	sleep_time;
	t_ui	max_food;
}		t_philo;

/*
**	Helper functions
*/

int	ft_atoi(const char *numstr);

#endif

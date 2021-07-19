/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/19 13:49:37 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	neg_check(t_philo *p)
{
	if (p->n_philos == UINT_MAX)
	{
		write(2, "Philosophers are not negative!\n", 32);
		return (1);
	}
	if (p->death_time == UINT_MAX)
	{
		write(2, "So, you mean they reincarnate?\n", 32);
		return (1);
	}
	if (p->eat_time == UINT_MAX)
	{
		write(2, "Aah yes, negative eating time, my favourite time.\n", 51);
		return (1);
	}
	if (p->sleep_time == UINT_MAX)
	{
		write(2, "The philosophers are not equal to an average student\n", 54);
		return (1);
	}
	return (0);
}

t_bool	init_philo(t_philo *p, int argc, char **argv)
{
	p->n_philos = (t_ui)ft_atoi(argv[1]);
	p->death_time = (t_ui)ft_atoi(argv[2]);
	p->eat_time = (t_ui)ft_atoi(argv[3]);
	p->sleep_time = (t_ui)ft_atoi(argv[4]);
	if (neg_check(p))
		return (1);
	if (argc == 6)
	{
		p->max_food = (t_ui)ft_atoi(argv[5]);
		if (p->max_food == UINT_MAX)
		{
			write(2, "You forgetti about the spaghetti, many regretti.\n", 50);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	p;

	if (argc != 6)
	{
		if (argc < 5)
		{
			write(2, "Not enough arguments.\n", 23);
			return (1);
		}
		else if (argc > 6)
		{
			write(2, "Too many arguments.\n", 21);
			return (1);
		}
	}
	if (init_philo(&p, argc, argv))
		return (1);
	return (0);
}

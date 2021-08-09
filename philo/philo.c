/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/09 17:09:10 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->message_mutex);
	ft_putnbr_ulong_fd(get_current_time() - philo->table->start_time, 1);
	if (philo->status != FULL_END)
	{
		ft_putstr_fd(" ms: Philosopher ", 1);
		ft_putnbr_ulong_fd(philo->position + 1, 1);
	}
	if (philo->status == TOOK_FORK)
		ft_putstr_fd(" took a fork in one of his hands.\n", 1);
	else if (philo->status == EATING)
		ft_putstr_fd(" is trying to dual wield eat spaghetti... Barbaric.\n", 1);
	else if (philo->status == SLEEPING)
		ft_putstr_fd(" is sleeping fast after too much spaghetti.\n", 1);
	else if (philo->status == THINKING)
		ft_putstr_fd(" is thinking about all the offended Italians.\n", 1);
	else if (philo->status == DEAD)
		ft_putstr_fd(" just died from starvation, such a cruel world.\n", 1);
	else if (philo->status == FULL_END)
		ft_putstr_fd("They had enough spaghetti! (┛◉Д◉)┛彡┻━┻\n.", 1);
	pthread_mutex_unlock(&philo->table->message_mutex);
}

/*
** only take forks when both are available!
*/

void	take_forks(t_philo *philo)
{
	int	ret1;
	int	ret2;

	ret1 = pthread_mutex_lock(&philo->table->forks_mutex[philo->left_fork]);
	ret2 = pthread_mutex_lock(&philo->table->forks_mutex[philo->right_fork]);
	if (ret1 == 0 && ret2 == 0)
	{
		philo->status = TOOK_FORK;
		message(philo);
		message(philo);
	}
	else if (ret1 != 0 && ret2 == 0)
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->left_fork]);
	else if (ret1 == 0 && ret2 != 0)
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->right_fork]);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->status = EATING;
	message(philo);
	usleep(philo->table->eat_time * ONE_MS);
	philo->time_since_eat = get_current_time();
	philo->new_death_time =
		philo->time_since_eat + philo->time_to_die;
	philo->eat_count++;
	pthread_mutex_unlock(&philo->philo_mutex);
}

/*
**	The current philosopher drops their forks and falls asleep
*/

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->right_fork]);
	philo->status = SLEEPING;
	message(philo);
	usleep(philo->table->sleep_time * ONE_MS);
}

/*void	*track_death(void *table)
{
	t_table	*t;
	t_philo	*p;

	t = (t_table *)table;
	p = &t->philo;
	while (TRUE)
	{
		pthread_mutex_lock(&p->philo_mutex);
		if (p->status != EATING && get_current_time() > p->new_death_time)
		{
			p->status = DEAD;
			message(t, p);
			pthread_mutex_unlock(&p->philo_mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&p->philo_mutex);
		usleep(ONE_MS);
	}
}*/

void	*philosophy_routine(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	p->time_since_eat = get_current_time();
	p->new_death_time = p->time_since_eat + p->time_to_die;
	while (TRUE)
	{
		take_forks(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		eating(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		sleeping(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
		p->status = THINKING;
		message(p);
		if (p->status == DEAD || p->status == FULL_END)
			break ;
	}
	return (NULL);
}

int	start_threads(t_table *t)
{
	int		i;
	t_philo	philo;

	t->start_time = get_current_time();
	i = -1;
	while (++i < t->n_philos)
	{
		philo = t->philos[i];
		philo.position = i;
		if (pthread_create(&philo.thread, NULL, philosophy_routine, (void *)&philo) == -1)
		{
			free(t->philos);
			return (1);
		}
	}
	i = -1;
	while (++i < t->n_philos)
		pthread_join(t->philos[i].thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	t;

	if (error_and_init(&t, argc, argv))
		return (error_exit(&t, "Data init error.\n", TRUE));
	init_philos(&t, t.philos, t.n_philos);
	if (init_mutexes(&t))
		return (error_exit(&t, "Mutex init error.\n", TRUE));
	if (start_threads(&t))
		return (error_exit(&t, "Thread error.\n", TRUE));
	clear_data(&t);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/29 13:31:22 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_table *t, t_philo *current_philo)
{
	pthread_mutex_lock(&t->message_mutex);
	ft_putnbr_ulong_fd(get_current_time() - current_philo->start_time, 1);
	if (current_philo->status != FULL_END)
	{
		ft_putstr_fd(" ms: Philosopher ", 1);
		ft_putnbr_ulong_fd(current_philo->position + 1, 1);
	}
	if (current_philo->status == TOOK_FORK)
		ft_putstr_fd(" took a fork in one of his hands.\n", 1);
	else if (current_philo->status == EATING)
		ft_putstr_fd(" is trying to dual wield eat spaghetti... Barbaric.\n", 1);
	else if (current_philo->status == SLEEPING)
		ft_putstr_fd(" is sleeping fast after too much spaghetti.\n", 1);
	else if (current_philo->status == THINKING)
		ft_putstr_fd(" is thinking about all the offended Italians.\n", 1);
	else if (current_philo->status == DEAD)
		ft_putstr_fd(" just died from starvation, such a cruel world.\n", 1);
	else if (current_philo->status == FULL_END)
		ft_putstr_fd(" They had enough spaghetti! (┛◉Д◉)┛彡┻━┻\n.", 1);
	pthread_mutex_unlock(&t->message_mutex);
}

void	take_forks(t_table *t, t_philo *current_philo)
{
	pthread_mutex_lock(&t->forks_mutex[current_philo->left_fork]);
	current_philo->status = TOOK_FORK;
	message(t, current_philo);
	pthread_mutex_lock(&t->forks_mutex[current_philo->left_fork]);
	message(t, current_philo);
}

void	eating(t_table *t, t_philo *current_philo)
{
	pthread_mutex_lock(&current_philo->philo_mutex);
	current_philo->status = EATING;
	current_philo->time_since_eat = get_current_time();
	current_philo->new_death_time =
		current_philo->time_since_eat - current_philo->time_to_die;
	message(t, current_philo);
	usleep(t->eat_time * ONE_MS);
	current_philo->eat_count++;
	current_philo->status = SLEEPING;
	pthread_mutex_unlock(&current_philo->philo_mutex);
}

/*
**	The current philosopher drops their forks and falls asleep
*/

void	sleeping(t_table *t, t_philo *current_philo)
{
	pthread_mutex_unlock(&t->forks_mutex[current_philo->left_fork]);
	pthread_mutex_unlock(&t->forks_mutex[current_philo->right_fork]);
	current_philo->status = SLEEPING;
	message(t, current_philo);
	usleep(t->sleep_time * ONE_MS);
}

void	*track_death(void *table)
{
	t_table	*t;
	t_philo	*p;

	t = (t_table *)table;
	p = &t->current_philo;
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
}

void	*philosophy(void *table)
{
	t_table		*t;
	t_philo		*p;
	pthread_t	status_tracker;

	t = (t_table *)table;
	p = &t->current_philo;
	p->time_since_eat = get_current_time();
	p->new_death_time = p->time_since_eat + p->time_to_die;
	if (pthread_create(&status_tracker, NULL, track_death, (void *)t) == -1)
		return ((void *)1);
	pthread_detach(status_tracker);
	while (TRUE)
	{
		take_forks(t, p);
		eating(t, p);
		sleeping(t, p);
		p->status = THINKING;
		message(t, p);
	}
	return (NULL);
}

int	start_threads(t_table *t)
{
	int			i;
	pthread_t	tid;
	void		*table;

	t->start_time = get_current_time();
	i = -1;
	while (++i < t->n_philos)
	{
		tid = t->philos[i].thread;
		t->philos[i].position = i;
		t->current_philo = t->philos[i];
		table = (void *)t;
		if (pthread_create(&tid, NULL, philosophy, table) == -1)
		{
			free(t->philos);
			return (1);
		}
		pthread_detach(tid);
		usleep(100);
	}
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

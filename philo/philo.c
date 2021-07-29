/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/29 12:12:39 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *current_philo)
{
	if (current_philo->status != FULL_END)
	{
		ft_putstr_fd("Philosopher ", 1);
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
		ft_putstr_fd("They had enough spaghetti! (┛◉Д◉)┛彡┻━┻\n.", 1);
}

void	take_forks(t_table *t, int who)
{
	pthread_mutex_lock(&t->forks_mutex[t->philos[who].left_fork]);
	message();
}

void	*track_death(void *current_philo)
{
	t_philo	*p;

	p = (t_philo *)current_philo;
	while (TRUE)
	{
		pthread_mutex_lock(&p->philo_mutex);
		if (p->status != EATING && get_current_time() > p->new_death_time)
		{
			p->status = DEAD;
			message(p);
			pthread_mutex_unlock(&p->philo_mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&p->philo_mutex);
		usleep(ONE_MS);
	}
}

void	*philosophy(void *current_philo)
{
	t_philo		*p;
	pthread_t	status_tracker;

	p = (t_philo *)current_philo;
	p->time_since_eat = get_current_time();
	p->new_death_time = p->time_since_eat + p->time_to_die;
	if (pthread_create(&status_tracker, NULL, track_death, current_philo) == -1)
		return ((void *)1);
	pthread_detach(status_tracker);
	while (TRUE)
	{
		take_forks()
		eat();
		sleep();
		think();
	}
	return (NULL);
}

int	start_threads(t_table *t)
{
	int			i;
	pthread_t	tid;
	void		*current_philo;

	t->start_time = get_current_time();
	i = -1;
	while (++i < t->n_philos)
	{
		tid = t->philos[i].thread;
		t->philos[i].position = i;
		current_philo = (void *)&t->philos[i];
		if (pthread_create(&tid, NULL, philosophy, current_philo) == -1)
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
	int		i;

	if (error_and_init(&t, argc, argv))
		return (error_exit(&t, "Data init error.\n", TRUE));
	init_philos(t.philos, t.n_philos);
	if (init_mutexes)
		return (error_exit(&t, "Mutex init error.\n", TRUE));
	return (0);
}

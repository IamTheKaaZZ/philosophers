/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:37:44 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/10 13:14:06 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo)
{
	static char	action_str[5][100] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	pthread_mutex_lock(philo->message_m);
	printf("%lld ms: Philosoper %d %s\n",
		get_current_time() - philo->start_time,
		philo->position + 1,
		action_str[philo->status]);
	pthread_mutex_unlock(philo->message_m);
}

t_bool	check_death(t_philo *p)
{
		pthread_mutex_lock(&p->philo_mutex);
		if (p->status != EATING && get_current_time() > p->new_death_time)
		{
			p->status = DEAD;
			message(p);
			pthread_mutex_unlock(&p->philo_mutex);
			return(TRUE);
		}
		pthread_mutex_unlock(&p->philo_mutex);
		return(FALSE);
}

/*
** only take forks when both are available!
*/

void	take_forks(t_philo *philo)
{
	t_bool	locked;

	locked = FALSE;
	while (!locked)
	{
		pthread_mutex_lock(philo->left_fork_m);
		pthread_mutex_lock(philo->right_fork_m);
		if (*philo->left_fork_state == FALSE
			&& *philo->right_fork_state == FALSE)
		{
			*philo->left_fork_state = TRUE;
			*philo->right_fork_state = TRUE;
			locked = TRUE;
		}
		pthread_mutex_unlock(philo->left_fork_m);
		pthread_mutex_unlock(philo->right_fork_m);
		if (locked)
		{
			philo->status = TOOK_FORK;
			message(philo);
			message(philo);
		}
		else
		{
			if (check_death(philo))
				return ;
		}
	}
}

void	eating(t_philo *philo)
{
	//pthread_mutex_lock(&philo->philo_mutex);
	philo->status = EATING;
	message(philo);
	usleep(philo->time_to_eat * ONE_MS);
	philo->time_ate = get_current_time();
	philo->new_death_time =
		philo->time_ate + philo->time_to_die;
	philo->eat_count++;
	//pthread_mutex_unlock(&philo->philo_mutex);
}

/*
**	The current philosopher drops their forks and falls asleep
*/

void	sleeping(t_philo *philo)
{
	t_ll	sleeptime;

	sleeptime = philo->time_to_sleep * ONE_MS;
	philo->status = SLEEPING;
	message(philo);
	pthread_mutex_lock(philo->left_fork_m);
	pthread_mutex_lock(philo->right_fork_m);
	*philo->left_fork_state = FALSE;
	*philo->right_fork_state = FALSE;
	pthread_mutex_unlock(philo->left_fork_m);
	pthread_mutex_unlock(philo->right_fork_m);
	while (sleeptime)
	{
		if (check_death(philo))
			return ;
		usleep(100);
		sleeptime -= 100;
	}
}

void	*philosophy_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
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

	t->start_time = get_current_time();
	i = -1;
	while (++i < t->n_philos)
	{
		t->philos[i].position = i;
		t->philos[i].start_time = t->start_time;
		if (pthread_create(&t->philos[i].thread,
				NULL,
				philosophy_routine,
				(void *)&t->philos[i])
				!= 0)
			return (1);
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
	if (init_mutexes(&t))
		return (error_exit(&t, "Mutex init error.\n", TRUE));
	init_philos(&t, t.philos, t.n_philos);
	if (start_threads(&t))
		return (error_exit(&t, "Thread error.\n", TRUE));
	//main thread should check for deaths and if they are all full
	// clear_data(&t);
	return (0);
}

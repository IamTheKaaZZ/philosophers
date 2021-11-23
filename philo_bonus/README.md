# Bonus

```
Program name:		philo_bonus
Turn in files:		philo_bonus/
Makefile:			Yes
Arguments:			number_of_philosophers time_to_die time_to_eat
					time_to_sleep [number_of_times_each_philosopher_must_eat]
External functs.:	memset, printf, malloc, free, write, fork, kill,
					exit, pthread_create, pthread_detach, pthread_join,
					usleep, gettimeofday, waitpid, sem_open, sem_close,
					sem_post, sem_wait, sem_unlink
Libft authorized:	No
Description:		philosopher with processes and semaphore
```
For the bonus part, the program takes the same arguments as before and should
behave as explained on the General Instructions chapter. The specific rules are:

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by
    a semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.
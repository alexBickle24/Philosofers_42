/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:14:10 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/27 07:55:25 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes all mutexes required for the simulation.
 * 
 * This function creates and initializes mutexes for forks, meal tracking, and
 * stopping conditions. Each philosopher has its own set of mutexes, ensuring
 * proper synchronization and avoiding data races. The `pthread_mutex_init`
 * function is used to allocate and initialize the mutexes in memory.
 * 
 * @param cond Pointer to the `t_cond` structure containing shared program state.
 * @return Returns 0 on success, or 1 if any mutex initialization fails.
 * 
 * @note Mutexes must be initialized before use to ensure thread safety. Failure
 * to initialize mutexes can lead to undefined behavior.
 */

char	create_mutex(t_cond *cond)
{
	int	i;
	int	ret1;
	int	ret2;
	int	ret4;

	i = 0;
	while (i < cond->n_philos)
	{
		ret1 = pthread_mutex_init(cond->m_forks[i], NULL);
		ret2 = pthread_mutex_init(cond->m_tmeal[i], NULL);
		ret4 = pthread_mutex_init(cond->m_stop[i], NULL);
		if (ret1 || ret2 || ret4)
			return (1);
		i++;
	}
	pthread_mutex_init(cond->m_fd, NULL);
	return (0);
}

/**
 * @brief Destroys all mutexes used in the simulation.
 * 
 * This function releases the resources associated with each mutex by calling
 * `pthread_mutex_destroy`. Destroying mutexes is essential to avoid memory
 * leaks and ensure that the operating system reclaims the resources. Each
 * mutex must be destroyed after all threads have finished using it.
 * 
 * @param cond Pointer to the `t_cond` structure containing shared program state.
 * @return Returns 0 on success, or 1 if any mutex destruction fails.
 * 
 * @note Failing to destroy mutexes can result in resource leaks, as the kernel
 * allocates memory for each mutex during initialization.
 */

char	destroy_mutex(t_cond *cond)
{
	int	i;
	int	ret1;
	int	ret2;
	int	ret4;

	i = 0;
	while (i < cond->n_philos)
	{
		ret1 = pthread_mutex_destroy(cond->m_forks[i]);
		ret2 = pthread_mutex_destroy(cond->m_tmeal[i]);
		ret4 = pthread_mutex_destroy(cond->m_stop[i]);
		if (ret1 || ret2 || ret4)
			return (1);
		i++;
	}
	pthread_mutex_destroy(cond->m_fd);
	return (0);
}

/**
 * @brief Creates threads for philosophers and the control routine.
 * 
 * This function spawns a thread for each philosopher using `pthread_create`.
 * Each thread executes the `game_r` routine, which simulates the philosopher's
 * behavior. Additionally, a control thread is created to monitor the simulation
 * state. If thread creation fails, allocated resources are freed to prevent
 * memory leaks.
 * 
 * @param cond Pointer to the `t_cond` structure containing shared program state.
 * @return Returns 0 on success, or 1 if any thread creation fails.
 * 
 * @note Threads are represented by Thread Control Blocks (TCBs), which are
 * allocated in memory by the operating system. Proper management of TCBs is
 * crucial to avoid resource exhaustion.
 */

char	create_threads(t_cond *cond)
{
	pthread_t	**threads;
	int			i;

	i = 0;
	threads = cond->threads;
	while (i < cond->n_philos)
	{
		if (pthread_create(threads[i], NULL, game_r, (void *)(cond->philos[i])))
			return (free_data(&cond), 1);
		i++;
	}
	if (pthread_create(cond->start_end_thread, NULL, control_r, (void *)cond))
		return (free_data(&cond), 1);
	return (0);
}

/**
 * @brief Joins all threads and handles the termination of the simulation.
 * 
 * This function waits for all philosopher threads and the control thread to
 * finish execution using `pthread_join`. The return value of the control thread
 * is used to determine if a philosopher has died. If a philosopher dies, its
 * ID and the time of death are printed.
 * 
 * @param conditions Pointer to the `t_cond` structure containing shared program
 * state.
 * 
 * @note Joining threads ensures that their resources, including the TCBs, are
 * properly released. Failing to join threads can lead to resource leaks and
 * undefined behavior.
 */

void	join_threads_and_printdie(t_cond *conditions)
{
	int			i;
	void		*retval;
	t_philo		*philo;
	int			id;
	long long	t_dead;

	i = 0;
	while (i < conditions->n_philos)
	{
		pthread_join(*(conditions->threads[i]), NULL);
		i++;
	}
	pthread_join(conditions->start_end_thread[0], &retval);
	if (retval != NULL)
	{
		philo = (t_philo *)retval;
		id = philo->mphilo_id;
		t_dead = conditions->dead - philo->init_time;
		printf("%lld %s%d%s", t_dead, YELLOW, id + 1, RESET);
		printf(" %sdied%s %s\n", RED, RESET, SKULL);
	}
}

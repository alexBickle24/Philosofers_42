/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:42:23 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/27 08:06:22 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Main routine executed by each philosopher thread.
 * 
 * This function initializes the philosopher's timestamps and handles their
 * behavior in the simulation. Philosophers alternate between eating, sleeping,
 * and thinking. If there is only one philosopher, they immediately enter a
 * waiting state (simulating starvation). Odd-numbered philosophers start with
 * a delay to avoid deadlocks.
 * 
 * @param arg Pointer to the philosopher's data structure (`t_philo`).
 * @return Always returns NULL when the thread terminates.
 * 
 * @note Synchronization is achieved using mutexes to ensure safe access to
 * shared resources, such as the time of the last meal.
 */

void	*game_r(void *arg)
{
	t_philo	*philo_i;

	philo_i = (t_philo *)arg;
	pthread_mutex_lock(philo_i->m_tmeal);
	philo_i->init_time = get_timestamp();
	philo_i->time_last_meal = get_timestamp();
	pthread_mutex_unlock(philo_i->m_tmeal);
	if (*(philo_i->n_philos) == 1)
	{
		melatonine(philo_i);
		return (NULL);
	}
	if ((philo_i->mphilo_id + 1) % 2 != 0)
		melatonine(philo_i);
	while (!stop_thread(philo_i))
	{
		if (jungle(philo_i))
			break ;
		if (melatonine(philo_i))
			break ;
	}
	return (NULL);
}

/**
 * @brief Simulates the sleeping phase of a philosopher.
 * 
 * This function makes the philosopher sleep for a specified duration. During
 * this time, the thread periodically checks if the simulation should stop to
 * avoid unnecessary delays. The sleep duration is divided into smaller intervals
 * using `usleep` to ensure responsiveness.
 * 
 * @param philo Pointer to the philosopher's data structure (`t_philo`).
 * @return Returns 1 if the thread should stop, or 0 otherwise.
 * 
 * @note Synchronizing sleep intervals reduces CPU usage and ensures that the
 * simulation remains responsive to changes in the `stop_game` flag.
 */

char	melatonine(t_philo *philo)
{
	long long	inicio;
	long long	time_doing;
	long long	usleep_t;

	inicio = get_timestamp();
	philo->timestamp = inicio - philo->init_time;
	if (stop_thread(philo))
		return (1);
	usleep_t = usleep_time_working(1);
	print_philo(philo, philo->mphilo_id, S_SLEEPING, philo->timestamp);
	time_doing = get_timestamp() - inicio;
	while (time_doing <= *(philo->t_sleep))
	{
		if (stop_thread(philo))
			return (1);
		usleep(usleep_t);
		time_doing = get_timestamp() - inicio;
	}
	if (thinking_on_nothing(philo))
		return (1);
	return (0);
}

/**
 * @brief Simulates the thinking phase of a philosopher.
 * 
 * This function updates the philosopher's state to "thinking" and prints the
 * corresponding message. It does not involve any time delays, as thinking is
 * considered an instantaneous action in this simulation.
 * 
 * @param philo Pointer to the philosopher's data structure (`t_philo`).
 * @return Returns 1 if the thread should stop, or 0 otherwise.
 */

char	thinking_on_nothing(t_philo *philo)
{
	if (stop_thread(philo))
		return (1);
	philo->timestamp = get_timestamp() - philo->init_time;
	philo->last_state = S_THINKING;
	print_philo(philo, philo->mphilo_id, S_THINKING, philo->timestamp);
	return (0);
}

/**
 * @brief Simulates the eating phase of a philosopher.
 * 
 * This function handles the philosopher's attempt to take forks, eat, and then
 * release the forks. All philosophers attempt to take the right fork first,
 * followed by the left fork. The order in which the forks are released depends
 * on the philosopher's position in the array. This ensures proper synchronization
 * and avoids deadlocks.
 * 
 * @param philo Pointer to the philosopher's data structure (`t_philo`).
 * @return Returns 1 if the thread should stop, or 0 otherwise.
 * 
 * @note Proper fork management is critical to avoid deadlocks. Philosophers
 * release the forks in a specific order: the last philosopher releases the
 * left fork first, while others release the right fork first.
 */

char	jungle(t_philo *philo)
{
	long long	usleep_t;
	long long	start;
	char		ret;

	if (stop_thread(philo))
		return (1);
	usleep_t = usleep_time_working(MS_FREC);
	if (take_forks(philo, &start))
		return (1);
	ret = gains(philo, start, usleep_t);
	if (philo->mphilo_id == *(philo->n_philos) - 1)
	{
		if (!drop_left_fork(philo) && !drop_right_fork(philo))
			return (ret);
	}
	else
	{
		if (!drop_right_fork(philo) && !drop_left_fork(philo))
			return (ret);
	}
	return (ret);
}

/**
 * @brief Handles the eating process and updates the philosopher's state.
 * 
 * This function makes the philosopher eat for a specified duration. During
 * this time, the thread periodically checks if the simulation should stop.
 * After eating, the philosopher's time of the last meal and meal count are
 * updated in a thread-safe manner using mutexes.
 * 
 * @param philo Pointer to the philosopher's data structure (`t_philo`).
 * @param inicio Timestamp when the eating phase started.
 * @param usleep_t Sleep interval for periodic checks.
 * @return Returns 1 if the thread should stop, or 0 otherwise.
 * 
 * @note Synchronizing access to the `time_last_meal` and `n_times_eats` fields
 * ensures that no data races occur when multiple threads access these fields.
 */

char	gains(t_philo *philo, long long inicio, long long usleep_t)
{
	long long	time_doing;

	time_doing = get_timestamp() - inicio;
	while (time_doing <= *(philo->t_eat))
	{
		if (stop_thread(philo))
			return (1);
		usleep(usleep_t);
		time_doing = get_timestamp() - inicio;
	}
	pthread_mutex_lock(philo->m_tmeal);
	philo->time_last_meal = get_timestamp();
	philo->n_times_eats++;
	pthread_mutex_unlock(philo->m_tmeal);
	return (0);
}

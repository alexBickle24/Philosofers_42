/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:27:30 by alcarril          #+#    #+#             */
/*   Updated: 2025/10/27 08:10:46 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Handles the process of taking both forks for a philosopher.
 * 
 * This function ensures that the philosopher takes the right fork first,
 * followed by the left fork. If the philosopher is the last one in the array,
 * the same order is followed. After successfully taking both forks, it checks
 * for any failure conditions (e.g., the simulation stopping) and handles them
 * appropriately.
 * 
 * @param philo Pointer to the philosopher's data structure (`t_philo`).
 * @param start Pointer to the timestamp when the forks were taken.
 * @return Returns 0 if the forks are successfully taken, or 1 if a failure occurs.
 * 
 * @note Proper synchronization is ensured using mutexes to prevent data races
 * when accessing the fork states. This function is critical for avoiding
 * deadlocks and ensuring smooth operation of the simulation.
 */

int	take_forks(t_philo *philo, long long *start)
{
	if (philo->mphilo_id == *(philo->n_philos) - 1)
	{
		if (!take_right_fork(philo, start) && !take_left_fork(philo, start))
		{
			if (fork_fail(philo))
				return (1);
		}
	}
	else
	{
		if (!take_right_fork(philo, start) && !take_left_fork(philo, start))
		{
			if (fork_fail(philo))
				return (1);
		}
	}
	return (0);
}

/**
 * @brief Handles failure conditions when taking forks.
 * 
 * This function checks if the simulation should stop while the philosopher
 * is attempting to take forks. If the simulation is stopping, it unlocks
 * any forks that the philosopher may have already taken to ensure that
 * other threads can proceed. If no failure occurs, it prints the philosopher's
 * eating state.
 * 
 * @param philo Pointer to the philosopher's data structure (`t_philo`).
 * @return Returns 1 if the simulation is stopping, or 0 otherwise.
 * 
 * @note This function ensures that resources (forks) are properly released
 * in case of a failure, preventing deadlocks and ensuring that other
 * philosophers can continue their operations.
 */

int	fork_fail(t_philo *philo)
{
	if (stop_thread(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_philo(philo, philo->mphilo_id, S_EATING, philo->timestamp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:56:04 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/27 08:09:37 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Attempts to take the right fork for the philosopher.
 * 
 * This function locks the mutex for the right fork and checks if the fork is
 * available. If the fork is available, it marks it as taken, updates the
 * philosopher's timestamp, and prints the corresponding message.
 * 
 * @param phi Pointer to the philosopher's data structure (`t_philo`).
 * @param start Pointer to the timestamp when the fork was taken.
 * @return Returns 0 if the fork is successfully taken, or 1 otherwise.
 * 
 * @note Mutexes ensure that only one philosopher can take the fork at a time,
 * preventing data races and ensuring proper synchronization.
 */

char	take_right_fork(t_philo *phi, long long *start)
{
	pthread_mutex_lock(phi->right_fork);
	if (!*(phi->fork_r))
	{
		*start = get_timestamp();
		phi->timestamp = *start - phi->init_time;
		*(phi->fork_r) = 1;
		print_philo(phi, phi->mphilo_id, S_TAKING_FORK_RIGHT, phi->timestamp);
		return (0);
	}
	return (1);
}

/**
 * @brief Attempts to take the left fork for the philosopher.
 * 
 * This function locks the mutex for the left fork and checks if the fork is
 * available. If the fork is available, it marks it as taken, updates the
 * philosopher's timestamp, and prints the corresponding message.
 * 
 * @param phi Pointer to the philosopher's data structure (`t_philo`).
 * @param start Pointer to the timestamp when the fork was taken.
 * @return Returns 0 if the fork is successfully taken, or 1 otherwise.
 * 
 * @note The same synchronization principles apply as with the right fork.
 */

char	take_left_fork(t_philo *phi, long long *start)
{
	pthread_mutex_lock(phi->left_fork);
	if (!*(phi->fork_l))
	{
		*start = get_timestamp();
		phi->timestamp = *start - phi->init_time;
		*(phi->fork_l) = 1;
		print_philo(phi, phi->mphilo_id, S_TAKING_FORK_LEFT, phi->timestamp);
		return (0);
	}
	return (1);
}

/**
 * @brief Releases the left fork for the philosopher.
 * 
 * This function marks the left fork as available and unlocks the corresponding
 * mutex. It ensures that other philosophers can access the fork after it is
 * released.
 * 
 * @param phi Pointer to the philosopher's data structure (`t_philo`).
 * @return Returns 0 if the fork is successfully released, or 1 otherwise.
 * 
 * @note Properly releasing forks is critical to avoid deadlocks and ensure
 * that all philosophers can progress in the simulation.
 */

char	drop_left_fork(t_philo *phi)
{
	if (*(phi->fork_l))
	{
		*(phi->fork_l) = 0;
		pthread_mutex_unlock(phi->left_fork);
		return (0);
	}
	return (1);
}

/**
 * @brief Releases the right fork for the philosopher.
 * 
 * This function marks the right fork as available and unlocks the corresponding
 * mutex. It ensures that other philosophers can access the fork after it is
 * released.
 * 
 * @param phi Pointer to the philosopher's data structure (`t_philo`).
 * @return Returns 0 if the fork is successfully released, or 1 otherwise.
 * 
 * @note The same principles apply as with the left fork.
 */

char	drop_right_fork(t_philo *phi)
{
	if (*(phi->fork_r))
	{
		*(phi->fork_r) = 0;
		pthread_mutex_unlock(phi->right_fork);
		return (0);
	}
	return (1);
}

/**
 * @brief Prints the current state of the philosopher.
 * 
 * This function locks the mutex for the output stream to ensure that messages
 * are printed without interference from other threads. It prints the
 * philosopher's ID, timestamp, and current state (e.g., sleeping, thinking,
 * eating, or taking a fork).
 * 
 * @param philo Pointer to the philosopher's data structure (`t_philo`).
 * @param id ID of the philosopher.
 * @param new_state The new state of the philosopher (e.g., S_SLEEPING, S_EATING).
 * @param timestamp The current timestamp in milliseconds.
 * 
 * @note Synchronizing access to the output stream prevents garbled or
 * overlapping messages when multiple threads attempt to print simultaneously.
 * This prevents data races in the output, ensuring that each message is
 * displayed correctly and in order.
 */

void	print_philo(t_philo *philo, int id, int new_state, long long timestamp)
{
	pthread_mutex_lock(philo->m_fd);
	printf("%lld %s%d%s", timestamp, YELLOW, id + 1, RESET);
	if (new_state == S_SLEEPING)
		printf(" %sis sleeping%s %s\n", LIGHT_BLUE, RESET, MOON);
	if (new_state == S_THINKING)
		printf(" %sis thinking%s %s\n", BLUE, RESET, BRAIN);
	if (new_state == S_TAKING_FORK_LEFT)
		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
	if (new_state == S_TAKING_FORK_RIGHT)
		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
	if (new_state == S_EATING)
		printf(" %sis eating%s %s\n", GREEN, RESET, STEAK);
	pthread_mutex_unlock(philo->m_fd);
}

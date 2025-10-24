/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarril <alcarril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:27:30 by alcarril          #+#    #+#             */
/*   Updated: 2025/10/12 23:49:48 by alcarril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

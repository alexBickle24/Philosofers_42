/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:56:04 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/20 01:01:08 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

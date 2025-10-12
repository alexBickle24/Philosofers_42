/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarril <alcarril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:42:23 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/12 23:49:41 by alcarril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

char	thinking_on_nothing(t_philo *philo)
{
	if (stop_thread(philo))
		return (1);
	philo->timestamp = get_timestamp() - philo->init_time;
	philo->last_state = S_THINKING;
	print_philo(philo, philo->mphilo_id, S_THINKING, philo->timestamp);
	return (0);
}

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

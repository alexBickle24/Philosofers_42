/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:14:10 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/20 01:18:26 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
		if (cond->n_philos >= 20)
		{
			if (pthread_mutex_init(cond->m_blockstart[i], NULL))
				return (1);
		}
		i++;
	}
	pthread_mutex_init(cond->m_fd, NULL);
	return (0);
}

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
		if (cond->n_philos >= 20)
		{
			if (pthread_mutex_destroy(cond->m_blockstart[i]))
				return (1);
		}
		i++;
	}
	pthread_mutex_destroy(cond->m_fd);
	return (0);
}

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

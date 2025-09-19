/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:14:10 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/19 17:14:00 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	create_philos_data(t_conditions *cond)
{
	int	i;

	cond->philos = (t_philo **)ft_calloc(sizeof(t_philo *), cond->n_philos);
	if (!cond->philos)
		return (1);
	i = -1;
	while (++i < cond->n_philos)
	{
		cond->philos[i] = (t_philo*)ft_calloc(sizeof(t_philo), 1);
		if (!cond->philos[i])
			return (1);
		cond->philos[i]->mphilo_id = i;
		if (i == 0)
			cond->philos[i]->left_fork = cond->m_forks[cond->n_philos - 1];
		else
			cond->philos[i]->left_fork = cond->m_forks[i - 1];
		cond->philos[i]->right_fork = cond->m_forks[i];
		cond->philos[i]->m_tmeal = cond->m_tmeal[i];
		cond->philos[i]->m_stop = cond->m_stop[i];
		cond->philos[i]->m_fd = cond->m_fd;
		cond->philos[i]->t_eat = &(cond->t_eat);
		cond->philos[i]->t_sleep = &(cond->t_sleep);
		cond->philos[i]->n_philos = &(cond->n_philos);
		cond->philos[i]->stop_game = &(cond->stop_game[i]);
	}
	return (0);
}

char	create_mutex(t_conditions *cond)
{
	int	i;
	int ret1;
	int ret2;
	int ret4;

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

char	destroy_mutex(t_conditions *cond)
{
	int	i;
	int ret1;
	int ret2;
	int ret4;

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

char	create_threads(t_conditions *cond)
{
	pthread_t	**threads;
	int	i;

	i = 0;
	threads = cond->threads;
	while(i < cond->n_philos)
	{	
		if (pthread_create(threads[i], NULL, game_r, (void *)(cond->philos[i])))
			return (free_data(&cond), 1);
		i++;
	}
	if (pthread_create(cond->start_end_thread, NULL, control_r, (void *)cond))
		return (free_data(&cond), 1);
	return (0);
}

void	join_threads_and_printdie(t_conditions *conditions)
{
	int i;
	void *retval;
	t_philo *philo;
	int id;
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
		t_dead =  conditions->dead -  philo->init_time;
		printf("%lld %s%d%s", t_dead, YELLOW, id + 1, RESET);
		printf(" %sdied%s %s\n", RED, RESET, SKULL);
	}
	// print_all_philos_eats(conditions);
	// print_all_philos_last_meal(conditions);
}

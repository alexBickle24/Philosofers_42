/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mthr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarril <alcarril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:33:39 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/12 23:49:30 by alcarril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	setup_multithread(t_cond *cond)
{
	if (prepare_threads(cond) || prepare_mutex(cond))
		return (free_data(&cond), 1);
	if (create_philos_data(cond))
		return (free_data(&cond), 1);
	return (0);
}

char	create_philos_data(t_cond *cond)
{
	int	i;

	cond->philos = (t_philo **)ft_calloc(sizeof(t_philo *), cond->n_philos);
	if (!cond->philos)
		return (1);
	i = -1;
	while (++i < cond->n_philos)
	{
		cond->philos[i] = (t_philo *)ft_calloc(sizeof(t_philo), 1);
		if (!cond->philos[i])
			return (1);
		cond->philos[i]->mphilo_id = i;
		if (i == 0)
		{
			cond->philos[i]->left_fork = cond->m_forks[cond->n_philos - 1];
			cond->philos[i]->fork_l = &(cond->forks[cond->n_philos - 1]);
		}
		else
		{
			cond->philos[i]->left_fork = cond->m_forks[i - 1];
			cond->philos[i]->fork_l = &(cond->forks[i - 1]);
		}
		create_philos_data2(cond, i);
	}
	return (0);
}

void	create_philos_data2(t_cond *cond, int i)
{
	cond->philos[i]->right_fork = cond->m_forks[i];
	cond->philos[i]->fork_r = &(cond->forks[i]);
	cond->philos[i]->m_tmeal = cond->m_tmeal[i];
	cond->philos[i]->m_stop = cond->m_stop[i];
	cond->philos[i]->m_fd = cond->m_fd;
	cond->philos[i]->t_eat = &(cond->t_eat);
	cond->philos[i]->t_sleep = &(cond->t_sleep);
	cond->philos[i]->n_philos = &(cond->n_philos);
	cond->philos[i]->stop_game = &(cond->stop_game[i]);
}

char	prepare_threads(t_cond *cond)
{
	int	i;
	int	n;

	n = cond->n_philos;
	i = 0;
	if (!cond)
		return (1);
	cond->threads = (pthread_t **)ft_calloc(sizeof(pthread_t *), n);
	if (!cond->threads)
		return (1);
	while (i < cond->n_philos)
	{
		cond->threads[i] = malloc(sizeof(pthread_t));
		if (cond->threads[i] == NULL)
			return (1);
		i++;
	}
	cond->start_end_thread = malloc(sizeof(pthread_t));
	if (cond->start_end_thread == NULL)
		return (1);
	return (0);
}

char	prepare_mutex(t_cond *con)
{
	int	i;
	int	n;

	n = con->n_philos;
	i = -1;
	if (!con)
		return (1);
	con->m_forks = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	con->m_tmeal = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	con->m_stop = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	if (!con->m_forks || !con->m_tmeal || !con->stop_game)
		return (1);
	while (++i < n)
	{
		con->m_forks[i] = malloc(sizeof(pthread_mutex_t));
		con->m_tmeal[i] = malloc(sizeof(pthread_mutex_t));
		con->m_stop[i] = malloc(sizeof(pthread_mutex_t));
		if (!con->m_forks[i] || !con->m_tmeal[i] || !con->m_stop[i])
			return (1);
	}
	con->m_fd = malloc(sizeof(pthread_mutex_t));
	if (!con->m_fd)
		return (1);
	return (0);
}

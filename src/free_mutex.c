/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_errors2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:12:01 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/19 14:40:56 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_fork_mutexes(t_conditions *conditions)
{
	int	i;

	if (conditions == NULL || conditions->m_forks == NULL)
		return;
	i = -1;
	while (++i < conditions->n_philos)
	{
		if (conditions->m_forks[i] != NULL)
		{
			free(conditions->m_forks[i]);
			conditions->m_forks[i] = NULL;
		}
	}
	free(conditions->m_forks);
	conditions->m_forks = NULL;
}

void	free_blockstart_mutexes(t_conditions *conditions)
{
	int	i;

	if (conditions == NULL || conditions->m_blockstart == NULL)
		return;
	i = -1;
	while (++i < conditions->n_philos)
	{
		if (conditions->m_blockstart[i] != NULL)
		{
			free(conditions->m_blockstart[i]);
			conditions->m_blockstart[i] = NULL;
		}
	}
	free(conditions->m_blockstart);
	conditions->m_blockstart = NULL;
}


void	free_tmeal_mutexes(t_conditions *conditions)
{
	int	i;

	if (conditions == NULL || conditions->m_tmeal == NULL)
		return;
	i = -1;
	while (++i < conditions->n_philos)
	{
		if (conditions->m_tmeal[i] != NULL)
		{
			free(conditions->m_tmeal[i]);
			conditions->m_tmeal[i] = NULL;
		}
	}
	free(conditions->m_tmeal);
	conditions->m_tmeal = NULL;
}

void	free_stop_mutexes(t_conditions *conditions)
{
	int	i;

	if (conditions == NULL || conditions->m_stop == NULL)
		return;
	i = -1;
	while (++i < conditions->n_philos)
	{
		if (conditions->m_stop[i] != NULL)
		{
			free(conditions->m_stop[i]);
			conditions->m_stop[i] = NULL;
		}
	}
	free(conditions->m_stop);
	conditions->m_stop = NULL;
}

void	free_all_mutexes(t_conditions *conditions)
{
	if (conditions == NULL)
		return;
	free(conditions->m_fd);
	free_stop_mutexes(conditions);
	free_blockstart_mutexes(conditions);
	free_fork_mutexes(conditions);
	free_tmeal_mutexes(conditions);
}

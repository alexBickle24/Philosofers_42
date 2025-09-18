/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:42:25 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/18 15:48:48 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_errorsargs(void)
{
	ft_putstr_fd("Error: Arguments error\n", 2);
	return (1);
}

int	ft_errorsargs1(void)
{
	ft_putstr_fd("Error: Invalid caracter in one argument\n", 2);
	return (1);
}

void	free_data(t_conditions **conditions)
{
	if (conditions == NULL)
		return ;
	free(conditions[0]->l_states);
	free(conditions[0]->stop_game);
	free_philosids(conditions[0]);
	free_all_mutexes(conditions[0]);
	free_threads(conditions[0]);
	free(conditions[0]);
	*conditions = NULL;
}

void	free_philosids(t_conditions *conditions)
{
	int	i;

	if (conditions == NULL || conditions->philos == NULL)
		return ;
	i = 0;
	while (i < conditions->n_philos)
	{
		if (conditions->philos[i] != NULL)
			free(conditions->philos[i]);
		i++;
	}
	free(conditions->philos);
	conditions->philos = NULL;
}

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

void	free_state_mutexes(t_conditions *conditions)
{
	int	i;

	if (conditions == NULL || conditions->m_state == NULL)
		return;
	i = -1;
	while (++i < conditions->n_philos)
	{
		if (conditions->m_state[i] != NULL)
		{
			free(conditions->m_state[i]);
			conditions->m_state[i] = NULL;
		}
	}
	free(conditions->m_state);
	conditions->m_state = NULL;
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
	free_stop_mutexes(conditions);
	free_blockstart_mutexes(conditions);
	free_fork_mutexes(conditions);
	free_state_mutexes(conditions);
	free_tmeal_mutexes(conditions);
}

void	free_threads(t_conditions *conditions)
{
	int	i;

	if (conditions == NULL || conditions->threads == NULL)
		return ;
	i = 0;
	while (i < conditions->n_philos)
	{
		if (conditions->threads[i] != NULL)
		{
			free(conditions->threads[i]);
			conditions->threads[i] = NULL;
		}
		i++;
	}
	free(conditions->threads);
	if(conditions->loggin_thread != NULL)
	{
		free(conditions->loggin_thread);
		conditions->loggin_thread = NULL;
	}
	if (conditions->start_end_thread != NULL)
	{
		free(conditions->start_end_thread);
		conditions->start_end_thread = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:12:01 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/27 07:41:49 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Frees memory allocated for fork mutexes.
 * 
 * This function iterates through the array of fork mutexes, freeing each one
 * individually. It also frees the array itself and sets the pointer to NULL
 * to prevent dangling references.
 * 
 * @param conditions Pointer to the `t_cond` structure containing fork mutexes.
 */

void	free_fork_mutexes(t_cond *conditions)
{
	int	i;

	if (conditions == NULL || conditions->m_forks == NULL)
		return ;
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

/**
 * @brief Frees memory allocated for meal mutexes.
 * 
 * This function iterates through the array of meal mutexes, freeing each one
 * individually. It also frees the array itself and sets the pointer to NULL
 * to prevent dangling references.
 * 
 * @param conditions Pointer to the `t_cond` structure containing meal mutexes.
 */

void	free_tmeal_mutexes(t_cond *conditions)
{
	int	i;

	if (conditions == NULL || conditions->m_tmeal == NULL)
		return ;
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
/**
 * @brief Frees memory allocated for stop mutexes.
 * 
 * This function iterates through the array of stop mutexes, freeing each one
 * individually. It also frees the array itself and sets the pointer to NULL
 * to prevent dangling references.
 * 
 * @param conditions Pointer to the `t_cond` structure containing stop mutexes.
 */

void	free_stop_mutexes(t_cond *conditions)
{
	int	i;

	if (conditions == NULL || conditions->m_stop == NULL)
		return ;
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

/**
 * @brief Frees all mutexes used in the simulation.
 * 
 * This function calls specific functions to free all types of mutexes used in
 * the simulation, including fork, meal, and stop mutexes. It ensures that all
 * allocated memory for mutexes is properly released.
 * 
 * @param conditions Pointer to the `t_cond` structure containing all mutexes.
 */

void	free_all_mutexes(t_cond *conditions)
{
	if (conditions == NULL)
		return ;
	free(conditions->m_fd);
	free_stop_mutexes(conditions);
	free_fork_mutexes(conditions);
	free_tmeal_mutexes(conditions);
}

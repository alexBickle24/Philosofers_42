/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:42:25 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/27 07:39:18 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Handles errors related to invalid arguments.
 * 
 * This function prints an error message to the standard error output
 * when the program encounters an issue with the provided arguments.
 * 
 * @return Always returns 1 to indicate an error.
 */

int	ft_errorsargs(void)
{
	ft_putstr_fd("Error: Arguments error\n", 2);
	return (1);
}

/**
 * @brief Handles errors caused by invalid characters in arguments.
 * 
 * This function prints an error message to the standard error output
 * when one of the arguments contains invalid characters.
 * 
 * @return Always returns 1 to indicate an error.
 */

int	ft_errorsargs1(void)
{
	ft_putstr_fd("Error: Invalid caracter in one argument\n", 2);
	return (1);
}

/**
 * @brief Frees all dynamically allocated memory in the `t_cond` structure.
 * 
 * This function ensures that all memory allocated for the simulation's
 * shared state is properly released. It includes freeing arrays, mutexes,
 * threads, and philosopher-specific data. After freeing, the pointer to
 * the `t_cond` structure is set to NULL to avoid dangling pointers.
 * 
 * @param conditions Double pointer to the `t_cond` structure to be freed.
 */

void	free_data(t_cond **conditions)
{
	if (conditions == NULL)
		return ;
	free(conditions[0]->stop_game);
	free(conditions[0]->sucess);
	free(conditions[0]->forks);
	free_philosids(conditions[0]);
	free_all_mutexes(conditions[0]);
	free_threads(conditions[0]);
	free(conditions[0]);
	*conditions = NULL;
}

/**
 * @brief Frees memory allocated for philosopher structures.
 * 
 * This function iterates through the array of philosopher structures,
 * freeing each one individually. It also frees the array itself and
 * sets the pointer to NULL to prevent dangling references.
 * 
 * @param conditions Pointer to the `t_cond` structure containing philosopher data.
 */

void	free_philosids(t_cond *conditions)
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

/**
 * @brief Frees memory allocated for thread structures.
 * 
 * This function releases memory allocated for the threads used in the simulation.
 * It ensures that each thread pointer is freed and set to NULL. Additionally,
 * it frees the `start_end_thread` array, which is used for thread synchronization.
 * 
 * @param conditions Pointer to the `t_cond` structure containing thread data.
 */

void	free_threads(t_cond *conditions)
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
	if (conditions->start_end_thread != NULL)
	{
		free(conditions->start_end_thread);
		conditions->start_end_thread = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:42:25 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/19 19:16:26 by alejandro        ###   ########.fr       */
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
	free(conditions[0]->stop_game);
	free(conditions[0]->sucess);
	free(conditions[0]->forks);
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
	if (conditions->start_end_thread != NULL)
	{
		free(conditions->start_end_thread);
		conditions->start_end_thread = NULL;
	}
}

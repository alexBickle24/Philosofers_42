/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:56:21 by alex              #+#    #+#             */
/*   Updated: 2025/10/27 18:52:21 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Entry point for the philosopher simulation program.
 * 
 * This function initializes the simulation by parsing arguments, setting up
 * multithreading, creating mutexes and threads, and managing cleanup. It
 * ensures proper resource allocation and deallocation throughout the program.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Returns 0 on successful execution, or 1 if an error occurs.
 */
int	main(int argc, char **argv)
{
	t_cond	*p_data;

	if (parsing_fill(&p_data, argv, argc))
		return (1);
	if (setup_multithread(p_data))
		return (1);
	create_mutex(p_data);
	create_threads(p_data);
	join_threads_and_printdie(p_data);
	destroy_mutex(p_data);
	free_data(&p_data);
	return (0);
}

/**
 * @brief Parses and validates command-line arguments.
 * 
 * This function checks the validity of the arguments provided to the program.
 * It ensures that the correct number of arguments is passed and that all
 * arguments are numeric and positive, as they represent time values and the
 * number of philosophers. If valid, it initializes the `t_cond` structure
 * with the parsed data.
 * 
 * @param p_data Double pointer to the `t_cond` structure to be initialized.
 * @param argv Array of command-line arguments.
 * @param argc Number of command-line arguments.
 * @return Returns 0 on success, or 1 if an error occurs.
 */
int	parsing_fill(t_cond **p_data, char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (ft_errorsargs());
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ft_errorsargs1());
			j++;
		}
		i++;
	}
	*p_data = fill_data(argv, argc);
	if (*p_data == NULL)
		return (1);
	return (0);
}

/**
 * @brief Allocates and fills the `t_cond` structure with parsed data.
 * 
 * This function initializes the `t_cond` structure with values parsed from
 * the command-line arguments. It ensures that the number of philosophers and
 * time values are positive. It also allocates memory for shared variables
 * such as `stop_game`, `sucess`, and `forks`. If any allocation fails, it
 * frees allocated resources and returns NULL.
 * 
 * @param argv Array of command-line arguments.
 * @param argc Number of command-line arguments.
 * @return Pointer to the initialized `t_cond` structure, or NULL on failure.
 */
t_cond	*fill_data(char **argv, int argc)
{
	t_cond	*p_data;

	p_data = (t_cond *)ft_calloc(sizeof(t_cond), 1);
	if (p_data == NULL)
		return (NULL);
	p_data->n_philos = ft_atoi(argv[1]);
	p_data->t_dead = ft_atoi(argv[2]);
	p_data->t_eat = ft_atoi(argv[3]);
	p_data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p_data->hm_eats = ft_atoi(argv[5]);
	else
		p_data->hm_eats = -1;
	p_data->stop_game = (int *)ft_calloc(sizeof(int), p_data->n_philos);
	p_data->sucess = (int *)ft_calloc(sizeof(int), p_data->n_philos);
	p_data->forks = (int *)ft_calloc(sizeof(int), p_data->n_philos);
	if (p_data->stop_game == NULL || p_data->sucess == NULL
		|| p_data->forks == NULL)
	{
		return (free_data(&p_data), NULL);
	}
	return (p_data);
}

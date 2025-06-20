/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:56:21 by alex              #+#    #+#             */
/*   Updated: 2025/06/20 14:17:50 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"


int main(int argc, char** argv)
{
	static p_conditions *p_data;

	if (parsing_imput_fill_data(p_data, argv, argc))
		return (1);//maybe free p_conditions
	//create trheads and mutex (one for philosofer)
	create_trheads(p_data)
	
	//start game execution
	
	
	//finish game and free memoria
	
	
}

int	parsing_imput_fill_data(p_conditions *p_data, char **argv, int argc)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 0);
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ft_putstr_fd("Error: Invalid caracter in one argument\n", 2), 0);
			j++;
		}
		i++;
	}
	p_data = fill_data(p_data, argv, argc);
	return (1);
}

p_conditions *fill_data(p_conditions *p_data, char **argv, int argc)
{
	int i;

	i = 0;
	p_data = (p_conditions*)malloc(sizeof(philo));
	if (p_data == NULL)
		return (NULL);
	p_data->n_philos = ft_atoi(argv[1]);
	p_data->t_dead = ft_atoi(argv[2]);
	p_data->t_think = ft_atoi(argv[3]);
	p_data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p_data->hm_eats = ft_atoi(argv[5]);
	p_data->forks = (int *)malloc(sizeof(p_data->n_philos));
	p_data->is_dead = (int *)malloc(sizeof(p_data->n_philos));
	if (p_data->forks == NULL || p_data->forks == NULL)
		return (NULL);
	ft_bzero((void *)p_data->forks, sizeof(p_data->forks));
	ft_bzero((void *)p_data->is_dead, sizeof(p_data->forks));
	p_data->stop_program = 0;
	return (p_data);
}

void	create_threads(p_conditions *conditions)
{
	pthread_mutex_t *mutex;
	pthread_t *ids; 
	int num_threads;

	num_threads = 0;
	ids = (pthread_t*)malloc(sizeof(pthread_mutex_t) * conditions->n_philos);
	if (!ids)
		return ;
	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * conditions->n_philos);
	if (!mutex)
		return (free(ids));
	conditions->philos = malloc(sizeof(philo) * conditions->n_philos);
	if (!conditions->philos)
		return ;
	//crear hilos
	//falta creear la condicion para cunado solo hay un hilo 
	while (num_threads < conditions->n_philos)
	{
		conditions->philos[num_threads].mphilo_id = num_threads + 1; 
		pthread_create(&(ids[num_threads]), NULL, /*rutina*/, conditions);
		num_threads++;
	}
	return ;
}


void threads_rutines(p_conditions *conditions)
{
	//quie es dosnde se hace el rearto de los recursos compartidos se modifican y se cierra el hilo
	//aqui es donde tengo que poner a comer a los impareas y a los pares, segun el id
	//tengo que poner tambien a pensar y a dormir
	
}

















/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:56:21 by alex              #+#    #+#             */
/*   Updated: 2025/09/19 19:27:24 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
	t_conditions *p_data;

	if (parsing_imput_fill_data(&p_data, argv, argc))
	{
		printf("sale por formating\n");
		return (1);
	}
	if (setup_multithread(p_data))
	{
		printf("sale por multithreating\n");
		return(1);
	}
	create_mutex(p_data);
	create_threads(p_data);
	join_threads_and_printdie(p_data);
	destroy_mutex(p_data);
	free_data(&p_data);
	return (0);
	
}

int	parsing_imput_fill_data(t_conditions **p_data, char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return(ft_errorsargs());
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return(ft_errorsargs1());
			j++;
		}
		i++;
	}
	*p_data = fill_data(argv, argc);
	if (*p_data == NULL)
		return (1);
	return (0);
}

t_conditions	*fill_data(char **argv, int argc)
{
	t_conditions *p_data;

	p_data = (t_conditions*)ft_calloc(sizeof(t_conditions), 1);
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
	if (p_data->stop_game == NULL || p_data->sucess == NULL || p_data->forks == NULL)
		return (free_data(&p_data), NULL);
	return (p_data);
}

char	setup_multithread(t_conditions *cond)
{
	if (prepare_threads(cond) || prepare_mutex(cond))
	{
		printf("falla 1\n");//
		return (free_data(&cond), 1);
	}
	if (create_philos_data(cond))
	{
		printf("falla 2\n");//
		return (free_data(&cond), 1);
	}
	return (0);
}

char	prepare_threads(t_conditions *cond)
{
	int	i;
	int n;

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

char	prepare_mutex(t_conditions *con)
{
	int	i;
	int n;

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
		if (!con->m_forks[i]  || !con->m_tmeal[i] || !con->m_stop[i])
			return (1);
	}
	con->m_fd = malloc(sizeof(pthread_mutex_t));
	if (!con->m_fd)
		return (1);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarril <alcarril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:56:21 by alex              #+#    #+#             */
/*   Updated: 2025/11/13 14:24:55 by alcarril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_atoi(const char *nptr)
{
	int	sing;
	int	num;

	sing = 1;
	num = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
	{
		nptr++;
	}
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
		{
			sing = -1;
		}
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (num * sing);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc((size * nmemb));
	if (!(ptr))
		return (NULL);
	while (i < (nmemb * size))
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}

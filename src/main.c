/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:56:21 by alex              #+#    #+#             */
/*   Updated: 2025/09/18 19:53:33 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
	t_conditions *p_data;

	if (parsing_imput_fill_data(&p_data, argv, argc))
		return (1);
	if (setup_multithread(p_data))
	{
		printf("sale por aqui\n");
		return(1);
	}
	//hata aqui funciona
	// print_conditions(p_data);//
	create_mutex(p_data);
	create_threads(p_data);
	join_threads_and_printdie(p_data);
	destroy_mutex(p_data);
	free_data(&p_data);
	return (0);
	
}

//Parseo de argumentos y estrcutura de control
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
	p_data->l_states = (int *)ft_calloc(sizeof(int), p_data->n_philos);
	p_data->stop_game = (int *)ft_calloc(sizeof(int), p_data->n_philos);
	if (p_data->l_states == NULL || p_data->stop_game == NULL)
		return (free_data(&p_data), NULL);
	return (p_data);
}

char	setup_multithread(t_conditions *cond)
{
	if (prepare_threads(cond) || prepare_mutex(cond))
	{
		printf("hdsaila\n");
		return (free_data(&cond), 1);
	}
	if (create_philos_data(cond))
	{
		printf("hila\n");
		return (free_data(&cond), 1);
	}
	return (0);
}

//preparar los recursos necesarios del proceso (hilos y mutex)
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
	// cond->loggin_thread = malloc(sizeof(pthread_t));
	cond->start_end_thread = malloc(sizeof(pthread_t));
	// if (cond->loggin_thread == NULL || cond->start_end_thread == NULL)
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
	con->m_state = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	con->m_tmeal = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	con->m_stop = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	if (!con->m_forks || !con->m_state || !con->m_tmeal || !con->stop_game)
		return (1);
	while (++i < n)
	{
		con->m_forks[i] = malloc(sizeof(pthread_mutex_t));
		con->m_state[i] = malloc(sizeof(pthread_mutex_t));
		con->m_tmeal[i] = malloc(sizeof(pthread_mutex_t));
		con->m_stop[i] = malloc(sizeof(pthread_mutex_t));
		if (!con->m_forks[i] || !con->m_state[i] || !con->m_tmeal[i]
			|| !con->m_stop[i])
		{
			return (1);
		}
	}
	if (n >= 20)
	{
		if (create_blockstart_mutex(con, n))
			return (1);
	}
	con->m_fd = malloc(sizeof(pthread_mutex_t));
	if (!con->m_fd)
		return (1);
	return (0);
}

char	create_blockstart_mutex(t_conditions *con, int n)
{
	int	i;

	i = -1;
	con->m_blockstart = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	if (!con->m_blockstart)
		return (1);
	while (++i < n)
	{
		con->m_blockstart[i] = malloc(sizeof(pthread_mutex_t));
		if (!con->m_blockstart[i])
			return (1);
	}
	return(0);
}
char	create_philos_data(t_conditions *cond)
{
	int	i;

	cond->philos = (t_philo **)ft_calloc(sizeof(t_philo *), cond->n_philos);
	if (!cond->philos)
		return (1);
	i = -1;
	while (++i < cond->n_philos)
	{
		cond->philos[i] = (t_philo*)ft_calloc(sizeof(t_philo), 1);
		if (!cond->philos[i])
			return (1);
		cond->philos[i]->mphilo_id = i;
		if (i == 0)
			cond->philos[i]->left_fork = cond->m_forks[cond->n_philos - 1];
		else
			cond->philos[i]->left_fork = cond->m_forks[i - 1];
		cond->philos[i]->right_fork = cond->m_forks[i];
		cond->philos[i]->m_state = cond->m_state[i];
		cond->philos[i]->m_tmeal = cond->m_tmeal[i];
		cond->philos[i]->m_stop = cond->m_stop[i];
		cond->philos[i]->t_eat = &(cond->t_eat);
		cond->philos[i]->t_sleep = &(cond->t_sleep);
		cond->philos[i]->n_philos = &(cond->n_philos);
		cond->philos[i]->stop_game = &(cond->stop_game[i]);
		cond->philos[i]->m_fd = cond->m_fd;
	}
	return (0);
}
//crear mutex e hilos 
char	create_mutex(t_conditions *cond)
{
	int	i;
	int ret1;
	int ret2;
	int ret3;
	int ret4;

	i = 0;
	while (i < cond->n_philos)
	{
		ret1 = pthread_mutex_init(cond->m_forks[i], NULL);
		ret2 = pthread_mutex_init(cond->m_tmeal[i], NULL);
		ret3 = pthread_mutex_init(cond->m_state[i], NULL);
		ret4 = pthread_mutex_init(cond->m_stop[i], NULL);
		if (ret1 || ret2 || ret3 || ret4)
			return (1);
		if (cond->n_philos >= 20)
		{
			if (pthread_mutex_init(cond->m_blockstart[i], NULL))
				return (1);
		}
		i++;
	}
	pthread_mutex_init(cond->m_fd, NULL);
	return (0);
}

char	destroy_mutex(t_conditions *cond)
{
	int	i;
	int ret1;
	int ret2;
	int ret3;
	int ret4;

	i = 0;
	while (i < cond->n_philos)
	{
		ret1 = pthread_mutex_destroy(cond->m_forks[i]);
		ret2 = pthread_mutex_destroy(cond->m_tmeal[i]);
		ret3 = pthread_mutex_destroy(cond->m_state[i]);
		ret4 = pthread_mutex_destroy(cond->m_stop[i]);
		if (ret1 || ret2 || ret3 || ret4)
			return (1);
		if (cond->n_philos >= 20)
		{
			if (pthread_mutex_destroy(cond->m_blockstart[i]))
				return (1);
		}
		i++;
	}
	pthread_mutex_destroy(cond->m_fd);
	return (0);
}


// crea los hilos con las rutinas, cunado falla no solo habriq eu liberar sino que habria 
// que hacer un jopin de los hilos, esto es problematico
char	create_threads(t_conditions *cond)
{
	pthread_t	**threads;
	int	i;

	
	i = 0;
	threads = cond->threads;
	// if (pthread_create(cond->loggin_thread, NULL, loggin_r, (void *)cond))
	// 	return (free_data(&cond), 1);
	if (pthread_create(cond->start_end_thread, NULL, control_r, (void *)cond))
		return (free_data(&cond), 1);
	while(i < cond->n_philos)
	{	
		if (pthread_create(threads[i], NULL, game_r, (void *)(cond->philos[i])))
			return (free_data(&cond), 1);
		i++;
	}
	return (0);
}

// Falseo la marca de tiempo.
void	join_threads_and_printdie(t_conditions *conditions)
{
	int i;
	void *retval;
	t_philo *philo;

	i = 0;
	pthread_join(conditions->start_end_thread[0], &retval);
	if (retval != NULL)
	{
		philo = (t_philo *)retval;
		if (!(conditions->hm_eats != -1 && philo->n_times_eats >= conditions->hm_eats))
			printf("%lld %d died\n", philo->time_last_meal + conditions->t_dead, philo->mphilo_id + 1);
	}
	ft_putstr_fd("dadsadasdasd\n", 2);
	while (i < conditions->n_philos)
	{
		ft_putstr_fd("esperando a hilos work\n", 2);
		pthread_join(*(conditions->threads[i]), NULL);
		i++;
	}
	// pthread_join(conditions->loggin_thread[0], NULL);

}

// void join_threads_and_printdie(t_conditions *conditions)
// {
//     int i;
//     void *retval;
//     t_philo *philo;

//     // 1️⃣ Esperar el hilo de control que detecta muerte o comidas
//     pthread_join(conditions->start_end_thread[0], &retval);

//     // // 2️⃣ Señalar a todos los hilos que deben detenerse
//     // parallel_stop(conditions);

//     // 3️⃣ Esperar a que todos los filósofos terminen
//     for (i = 0; i < conditions->n_philos; i++)
//         pthread_join(*(conditions->threads[i]), NULL);

//     // 4️⃣ Esperar al hilo de logging
//     pthread_join(conditions->loggin_thread[0], NULL);

//     // 5️⃣ Imprimir muerte si corresponde
//     if (retval != NULL)
//     {
//         philo = (t_philo *)retval;
//         if (!(conditions->hm_eats != -1 && philo->n_times_eats >= conditions->hm_eats))
//             printf("%lld %d died\n", philo->time_last_meal + conditions->t_dead, philo->mphilo_id + 1);
//     }
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:56:21 by alex              #+#    #+#             */
/*   Updated: 2025/09/15 15:24:21 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
	t_conditions *p_data;

	if (parsing_imput_fill_data(&p_data, argv, argc))
		return (1);
	if (setup_multithread(p_data))
		return(1);
	//hata aqui funciona
	print_conditions(p_data);//
	
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
	p_data->t_think = ft_atoi(argv[3]);
	p_data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p_data->hm_eats = ft_atoi(argv[5]);
	else
		p_data->hm_eats = -1;
	p_data->l_states = (int *)ft_calloc(sizeof(int), p_data->n_philos);
	if (p_data->l_states == NULL)
		return (free_data(&p_data), NULL);
	return (p_data);
}

char	setup_multithread(t_conditions *cond)
{
	if (!prepare_threads(cond) || !prepare_mutex(cond))
		return (free_data(&cond), 1);
	if (create_philos_data(cond))
		return (free_data(&cond), 1);
	return (0);
}

//Crear los recursso necesairos para cada philo
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
		if (i == cond->n_philos - 1)
			cond->philos[i]->right_fork = cond->m_forks[0];
		else
			cond->philos[i]->right_fork = cond->m_forks[i + 1];
		cond->philos[i]->m_state = cond->m_state[i];
		cond->philos[i]->m_tmeal = cond->m_tmeal[i];
		cond->philos[i]->m_stop = cond->m_stop;
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
	cond->loggin_thread = malloc(sizeof(pthread_t));
	cond->start_end_thread = malloc(sizeof(pthread_t));
	if (cond->loggin_thread == NULL || cond->start_end_thread == NULL)
		return (1);	
	return (0);
}

char	prepare_mutex(t_conditions *con)
{
	int	i;
	int n;

	n = con->n_philos;
	i = 0;
	if (!con)
		return (1);
	con->m_forks = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	con->m_state = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	con->m_tmeal = (pthread_mutex_t **)ft_calloc(sizeof(pthread_mutex_t *), n);
	if (!con->m_forks || !con->m_state || !con->m_tmeal)
		return (1);
	while (i < n)
	{
		con->m_forks[i] = malloc(sizeof(pthread_mutex_t));
		con->m_state[i] = malloc(sizeof(pthread_mutex_t));
		con->m_tmeal[i] = malloc(sizeof(pthread_mutex_t));
		if (!con->m_forks[i] || !con->m_state[i] || !con->m_tmeal[i])
			return (1);
		i++;
	}
	con->m_stop = malloc(sizeof(pthread_mutex_t));
	if (con->m_stop == NULL)
		return (1);
	return (0);
}

//crear mutex e hilos 
char	create_mutex(t_conditions *cond)
{
	int	i;
	int ret1;
	int ret2;
	int ret3;

	i = 0;
	while (i <= cond->n_philos)
	{
		ret1 = pthread_mutex_init(cond->m_forks[i], NULL);
		ret2 = pthread_mutex_init(cond->m_tmeal[i], NULL);
		ret3 = pthread_mutex_init(cond->m_state[i], NULL);
		if (ret1 || ret2 || ret3)
			return (1);
		i++;
	}
	if (pthread_mutex_init(cond->m_stop, NULL))
		return (1);
	return (0);
}

char	destroy_mutex(t_conditions *cond)
{
	int	i;
	int ret1;
	int ret2;
	int ret3;

	i = 0;
	while (i <= cond->n_philos)
	{
		ret1 = pthread_mutex_destroy(cond->m_forks[i]);
		ret2 = pthread_mutex_destroy(cond->m_tmeal[i]);
		ret3 = pthread_mutex_destroy(cond->m_state[i]);
		if (ret1 || ret2 || ret3)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(cond->m_stop))
		return (1);
	return (0);
}


// crea los hilos con las rutinas, cunado falla no solo habriq eu liberar sino que habria 
// que hacer un jopin de los hilos, esto es problematico
char	create_threads(t_conditions *cond)
{
	pthread_t	**threads;
	t_philo	**philos;
	int	i;

	i = 1;
	threads = cond->threads;
	if (pthread_create(cond->loggin_thread, NULL, loggin_r, (void *)cond))
		return (free_data(cond), 1);
	if (pthread_create(cond->start_end_thread, NULL, control_r, (void *)cond))
		return (free_data(cond), 1);
	while(i < cond->n_philos)
	{	
		if (pthread_create(threads[i], NULL, game_r, (void *)philos[i]))
			return (free_data(cond), 1);
		i++;
	}
}

//crear manejadores de los hilos
void	*control_r(void *arg)
{
	while (1)
	{
		//por cada philo bloquear el mutex de m_state, leer last_meal y comprar con 
		//marca de tiempo actual y con teimpo de muerte, si llega a ese timpo se devuel
		//ve 1. tambien se compara con numeero de veces maximo de comidas si llega a ese numero
		//se retorna 2.
	}
	//despues se imprime el filofo que ha muerto y su marca de tiempo 
}


//Esta es la rutina que escribe en la stdout
void	*loggin_r(void *arg)
{
	t_conditions *cond;
	int	i;

	cond = (t_conditions *)arg;
	i = 0;
	while (i < cond->n_philos)
	{
		cond->l_states[i] = S_INIT;
		i++;
	}
	//Cuando el estado del filosofo es diferente al estado de la tabla de last state
	//se imrime el mensaje y la marca de tiempo. Casos especiales:
	//Cuando el estado es tanking a fork y el estado anterior es taking a forkriht
	//se imprmir taking a fork y depsues se imprime is eating.
}

void	*game_r(void *arg)
{
	t_philo	*philo_i;

	philo_i = (t_philo *)arg;
	//poner last meal al tiempo actual
	
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:29:14 by alex              #+#    #+#             */
/*   Updated: 2025/09/19 13:27:36 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "../libft/libft.h"
#include "colors.h"
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define MS_FREC 5

typedef enum s_philo_state
{
	S_INIT,
	S_TAKING_FORK_LEFT,
	S_TAKING_FORK_RIGHT,
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DIED,
}	t_philo_state;

//Datos del filosofo
typedef struct philo_data
{

	long long	*t_eat;
	long long	*t_sleep;
	int			*n_philos;
	int			mphilo_id;//qur nuemro de filofo es 
	long long	time_last_meal;//(escribe philo -  lee start_end)
	int			n_times_eats;//(escribe philo - lee start_end)
	long long	timestamp;//para el ultimo cambio de estado del philosofo
	int			last_state;//(escribe philo - lee logging)
	int			*stop_game;
	long long	init_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m_fd;//un mutex para cada fork (philos-philos)
	pthread_mutex_t	*m_state;//para cambio de estado (philos-loggin)
	pthread_mutex_t	*m_tmeal;//para cambio de ultima comida y numero de comidas(philos-start_end)
	pthread_mutex_t	*m_stop;//para consultar cuando se esta comiendo y liberar el mutex (start_end - philos)
}		t_philo;

//Estrcutura con los datos de los arguemtnos de los philososofos
typedef struct program_conditions
{
	int			n_philos;
	long long	t_dead;
	long long	t_sleep;
	long long	t_eat;
	long long	hm_eats;
	int			start;//
	long long	dead;
	int			*sucess;
	int			*stop_game; //esta variable solo se escribe desde hilo control y leen continuamente los hilos de ejecucion.
	pthread_t	**threads;//los hilos de los filofofos (handler)
	pthread_t	*start_end_thread;//el hilo de comprobacion de muerte
	pthread_mutex_t	*m_fd;//un mutex para cada fork (philos-philos);
	pthread_mutex_t	**m_forks;//un mutex para cada fork (philos-philos)
	pthread_mutex_t	**m_blockstart;//un mutex para cada fork (philos-philos)
	pthread_mutex_t	**m_state;//para cambio de estado (philos-loggin)
	pthread_mutex_t	**m_tmeal;//para cambio de ultima comida y numero de comidas(philos-start_end)
	pthread_mutex_t	**m_stop;//para que los philos la lean y comprueben si tiene que liberar el mutex
	t_philo	**philos;//datos de control de cada philosofo
}	t_conditions;

//debugin
void print_conditions(t_conditions *conditions);

//free and close
void	free_data(t_conditions **conditions);
void	free_philosids(t_conditions *conditions);
void	free_all_mutexes(t_conditions *conditions);
void	free_blockstart_mutexes(t_conditions *conditions);
void	free_stop_mutexes(t_conditions *conditions);
void	free_tmeal_mutexes(t_conditions *conditions);
void	free_state_mutexes(t_conditions *conditions);
void	free_fork_mutexes(t_conditions *conditions);
void	free_threads(t_conditions *conditions);
int		ft_errorsargs(void);
int		ft_errorsargs1(void);

//parsing arguments
t_conditions	*fill_data(char **argv, int argc);
int	parsing_imput_fill_data(t_conditions **p_data, char **argv, int argc);

//setup multithreating
char	setup_multithread(t_conditions *cond);
char	create_philos_data(t_conditions *cond);
char	prepare_threads(t_conditions *cond);
char	prepare_mutex(t_conditions *con);
char	create_blockstart_mutex(t_conditions *con, int n);
char	create_mutex(t_conditions *cond);

//create threads
char	create_threads(t_conditions *cond);
char	destroy_mutex(t_conditions *cond);

//rutines
void	*control_r(void *arg);
void	parallel_stop(t_conditions *con);
char	check_sucess(t_conditions *cond, int i, int hm_meals);
void	*game_r(void *arg);
char	melatonine(t_philo *philo);
char	thinking_on_nothing(t_philo *philo);
char	jungle(t_philo *philo);
char	gains(t_philo *philo, long long inicio, long long usleep_t);
char	stop_thread(t_philo *philo_i);
void	print_philo(t_philo *philos, int id, int new_state, long long timestamp);

//time
long long	usleep_time_loggin(t_conditions *cond);
long long 	usleep_time_controler(int num_philos, int frec_pp);
long long 	usleep_time_working(int frec_pp);
long long	get_timestamp(void);

//join_threads and destroy mutex
void	join_threads_and_printdie(t_conditions *conditions);

//destroy multithreating
char	destroy_mutex(t_conditions *cond);





#endif




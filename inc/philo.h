/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:29:14 by alex              #+#    #+#             */
/*   Updated: 2025/09/15 15:25:42 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "../libft/libft.h"
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>

typedef enum s_philo_state
{
	S_INIT,
	S_EATING,
	S_TAKING_FORK_LEFT,
	S_TAKING_FORK_RIGHT,
	S_SLEEPING,
	S_THINKING,
	S_DIED,
}	t_philo_state;

//Datos del filosofo
typedef struct philo_data
{
	int	mphilo_id;//qur nuemro de filofo es 
	int	last_meal;//(escribe philo -  lee start_end)
	int	n_times_eats;//(escribe philo - lee start_end)
	unsigned int time_eat;//como funciona
	int	last_state;//(escribe philo - lee logging)
	int	forks[2];//cuando los tenga es que esta comiendo
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m_state;//para cambio de estado (philos-loggin)
	pthread_mutex_t	*m_tmeal;//para cambio de ultima comida y numero de comidas(philos-start_end)
	pthread_mutex_t	*m_stop;//para consultar cuando se esta comiendo y liberar el mutex (start_end - philos)
	struct timeval tv;
}		t_philo;

//Estrcutura con los datos de los arguemtnos de los philososofos
typedef struct program_conditions
{
	int	n_philos;
	int	t_dead;
	int	t_think;
	int	t_sleep;
	int	t_eat;
	int	hm_eats;
	char	stop_game; //esta variable solo se escribe desde hilo control y leen continuamente los hilos de ejecucion.
	int **l_states;//los estados de cada philosofo (solo lee y escribe logging)
	pthread_t	**threads;//los hilos de los filofofos (handler)
	pthread_t	*loggin_thread;//el hilo de escritura (handler)
	pthread_t	*start_end_thread;//el hilo de comprobacion de muerte
	pthread_mutex_t	**m_forks;//un mutex para cada fork (philos-philos)
	pthread_mutex_t	**m_state;//para cambio de estado (philos-loggin)
	pthread_mutex_t	**m_tmeal;//para cambio de ultima comida y numero de comidas(philos-start_end)
	pthread_mutex_t	*m_stop;//para que los philos la lean y comprueben si tiene que liberar el mutex
	t_philo	**philos;//datos de control de cada philosofo
}	t_conditions;

//debugin
void print_conditions(t_conditions *conditions);

//free and close
void	free_data(t_conditions **conditions);
void	free_philosids(t_conditions *conditions);
void	free_all_mutexes(t_conditions *conditions);
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
char	create_mutex(t_conditions *cond);

//destroy multithreating
char	destroy_mutex(t_conditions *cond);
//hacer el join de los hilos

//start game

//rutines




#endif




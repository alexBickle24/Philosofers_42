/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarril <alcarril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:29:14 by alex              #+#    #+#             */
/*   Updated: 2025/10/12 23:50:03 by alcarril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include "colors.h"
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

# define MS_FREC 5

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
	long long		*t_eat;
	long long		*t_sleep;
	int				*n_philos;
	int				mphilo_id;
	long long		time_last_meal;
	int				n_times_eats;
	long long		timestamp;
	int				last_state;
	int				*stop_game;
	long long		init_time;
	int				*fork_r;
	int				*fork_l;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m_fd;
	pthread_mutex_t	*m_tmeal;
	pthread_mutex_t	*m_stop;
	//blockstart
}		t_philo;

//Estrcutura con los datos de los arguemtnos de los philososofos
typedef struct program_conditions
{
	int				n_philos;
	long long		t_dead;
	long long		t_sleep;
	long long		t_eat;
	long long		hm_eats;
	int				start;//
	long long		dead;
	int				*forks;
	int				*sucess;
	int				*stop_game;
	pthread_t		**threads;
	pthread_t		*start_end_thread;
	pthread_mutex_t	*m_fd;
	pthread_mutex_t	**m_forks;
	pthread_mutex_t	**m_blockstart;//
	pthread_mutex_t	**m_tmeal;
	pthread_mutex_t	**m_stop;
	t_philo			**philos;
}	t_cond;

//debugin
void		print_all_philos_eats(t_cond *conditions);
void		print_all_philos_fields(t_cond *conditions);
void		print_all_philos_last_meal(t_cond *conditions);

//free and close
void		free_data(t_cond **conditions);
void		free_philosids(t_cond *conditions);
void		free_all_mutexes(t_cond *conditions);
void		free_stop_mutexes(t_cond *conditions);
void		free_tmeal_mutexes(t_cond *conditions);
void		free_fork_mutexes(t_cond *conditions);
void		free_threads(t_cond *conditions);
int			ft_errorsargs(void);
int			ft_errorsargs1(void);

//parsing arguments
t_cond		*fill_data(char **argv, int argc);
int			parsing_fill(t_cond **p_data, char **argv, int argc);

//setup multithreating
char		setup_multithread(t_cond *cond);
char		create_philos_data(t_cond *cond);
void		create_philos_data2(t_cond *cond, int i);
char		prepare_threads(t_cond *cond);
char		prepare_mutex(t_cond *con);

//create threads
char		create_threads(t_cond *cond);
char		create_mutex(t_cond *cond);
char		destroy_mutex(t_cond *cond);
void		join_threads_and_printdie(t_cond *conditions);

//rutines control
void		*control_r(void *arg);
void		parallel_stop(t_cond *con);
char		check_sucess(t_cond *cond, int i, int hm_meals);
long long	get_philo_values(int *eat, t_cond *con, int i);

//rutines game
void		*game_r(void *arg);
char		melatonine(t_philo *philo);
char		thinking_on_nothing(t_philo *philo);
char		jungle(t_philo *philo);
char		gains(t_philo *philo, long long inicio, long long usleep_t);
char		drop_right_fork(t_philo *phi);
char		drop_left_fork(t_philo *phi);
int			take_forks(t_philo *philo, long long *start);
char		take_right_fork(t_philo *phi, long long *start);
char		take_left_fork(t_philo *phi, long long *start);
int			fork_fail(t_philo *philo);
void		print_philo(t_philo *philos, int id, int new_state,
				long long timestamp);

//time
long long	usleep_time_controler(int num_philos, int frec_pp);
long long	usleep_time_working(int frec_pp);
long long	get_timestamp(void);
char		stop_thread(t_philo *philo_i);

#endif
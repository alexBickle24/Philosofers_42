/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggin_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:04:16 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/18 19:42:24 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//creo que esta bien pero falta la sincronixacion de inicio
// void	*loggin_r(void *arg)
// {
// 	t_conditions	*cond;
// 	int	i;
// 	int last_state;
// 	int	usleep_time;

// 	cond = (t_conditions *)arg;
// 	usleep_time = usleep_time_loggin(cond);
// 	i = -1;
// 	while (++i < cond->n_philos)
// 	{
// 		pthread_mutex_lock(cond->m_stop[i]);
// 		if (cond->stop_game[i])
// 		{
// 			pthread_mutex_unlock(cond->m_stop[i]);
// 			break ;
// 		}
// 		pthread_mutex_unlock(cond->m_stop[i]);
// 		pthread_mutex_lock(cond->m_state[i]);
// 		last_state = cond->philos[i]->last_state;
// 		pthread_mutex_unlock(cond->m_state[i]);
// 		if(cond->l_states[i] != last_state)
// 		{
// 			print_philo_state(cond, i, last_state);
// 			cond->l_states[i] = last_state;
// 		}
// 		if (i == cond->n_philos - 1)
// 			i = -1;
// 		usleep(usleep_time * 1);
// 	}
// 	return (NULL);
// }

// #include <unistd.h>
// #include <stdio.h>  // solo para snprintf

// void print_philo_state(t_conditions *cond, int id, int new_state, int prevstate)
// {
//     char buffer[256];
//     int len;
//     long long ts = cond->philos[id]->timestamp;

//     // Estado sleeping
//     if (new_state == S_SLEEPING)
//     {
//         len = snprintf(buffer, sizeof(buffer), "%lld %d is sleeping 🌙\n", ts, id + 1);
//         write(1, buffer, len);
//     }
//     // Estado thinking
//     else if (new_state == S_THINKING)
//     {
//         len = snprintf(buffer, sizeof(buffer), "%lld %d is thinking 🧠\n", ts, id + 1);
//         write(1, buffer, len);
//     }
//     // Estado fork left
//     else if (new_state == S_TAKING_FORK_LEFT)
//     {
//         len = snprintf(buffer, sizeof(buffer), "%lld %d has taken a fork left 🍴\n", ts, id + 1);
//         write(1, buffer, len);

//         if (prevstate == S_TAKING_FORK_RIGHT)
//         {
//             len = snprintf(buffer, sizeof(buffer), "%lld %d is eating 🥩\n", ts, id + 1);
//             write(1, buffer, len);
//         }
//     }
//     // Estado fork right
//     if (prevstate == S_TAKING_FORK_RIGHT)
//     {
//         len = snprintf(buffer, sizeof(buffer), "%lld %d has taken a fork right 🍴\n", ts, id + 1);
//         write(1, buffer, len);

//         if (cond->l_states[id] == S_TAKING_FORK_LEFT)
//         {
//             len = snprintf(buffer, sizeof(buffer), "%lld %d is eating 🥩\n", ts, id + 1);
//             write(1, buffer, len);
//         }
//     }
// }


// void	print_philo_state(t_conditions *cond, int id, int new_state)
// {
// 	printf("%lld %s%d%s", cond->philos[id]->timestamp, YELLOW, id + 1, RESET);
// 	if (new_state == S_SLEEPING)
// 		printf(" %sis sleeping%s %s\n", LIGHT_BLUE, RESET, MOON);
// 	if (new_state == S_THINKING)
// 		printf(" %sis thinking%s %s\n", BLUE, RESET, BRAIN);
// 	if (new_state == S_TAKING_FORK_LEFT) 
// 		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
// 	if (new_state == S_TAKING_FORK_RIGHT)
// 		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
// 	if (new_state == S_EATING)
// 	{
// 		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
// 		printf("%lld %s%d%s", cond->philos[id]->timestamp, YELLOW, id + 1, RESET);
// 		printf(" %sis esting%s %s\n", GREEN, RESET, STEAK);
// 	}
// }

void	*control_r(void *arg)
{
	t_conditions	*cond;
	long long		usleep_t;
	long long		time_last_meal;
	int				hm_meals;
	int				i;
	
	cond = (t_conditions *)arg;
	usleep_t = usleep_time_controler(cond->n_philos, MS_FREC - 1);
	i = -1;
	while (++i < cond->n_philos)
	{
		pthread_mutex_lock(cond->m_tmeal[i]);
		time_last_meal = cond->philos[i]->time_last_meal;
		hm_meals = cond->philos[i]->n_times_eats;
		pthread_mutex_unlock(cond->m_tmeal[i]);
		if ((cond->hm_eats != -1 && hm_meals >= cond->hm_eats) ||
			(get_timestamp() - time_last_meal) >= cond->t_dead)
		{
			parallel_stop(cond);
			return((void *)cond->philos[i]);// o retornar el philsosof en cuestion
		}
		if (i == cond->n_philos - 1)
			i = -1;
		usleep(usleep_t);//mayor frercuedncia
	}
	return (NULL);
}

void	parallel_stop(t_conditions *con)
{
	int	i;

	i = 0;
	while (i < con->n_philos)
	{
		pthread_mutex_lock(con->m_stop[i]);
		con->stop_game[i] = 1;
		pthread_mutex_unlock(con->m_stop[i]);
		i++;
	}
}

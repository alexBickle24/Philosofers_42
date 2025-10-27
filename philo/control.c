/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:04:16 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/27 07:36:34 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Monitors the state of philosophers and enforces stopping conditions.
 * 
 * This function runs in a dedicated thread and continuously monitors the state
 * of all philosophers. It checks for conditions such as starvation (time since
 * last meal exceeding the death threshold) or success (all philosophers have
 * eaten the required number of meals). Mutexes and controlled sleep intervals
 * are used to ensure thread safety and avoid excessive CPU usage.
 * 
 * @param arg Pointer to the `t_cond` structure containing shared program state.
 * @return Returns a pointer to the philosopher who died, or NULL if success conditions are met.
 */

void	*control_r(void *arg)
{
	t_cond			*cond;
	long long		usleep_t;
	long long		time_last_meal;
	int				hm_meals;
	int				i;

	cond = (t_cond *)arg;
	usleep_t = usleep_time_controler(cond->n_philos, MS_FREC);
	i = -1;
	while (++i < cond->n_philos)
	{
		time_last_meal = get_philo_values(&hm_meals, cond, i);
		if ((get_timestamp() - time_last_meal) >= cond->t_dead)
		{
			cond->dead = get_timestamp();
			parallel_stop(cond);
			return ((void *)cond->philos[i]);
		}
		if (check_sucess(cond, i, hm_meals))
			return (NULL);
		if (i == cond->n_philos - 1)
			i = -1;
		usleep(usleep_t);
	}
	return (NULL);
}

/**
 * @brief Safely retrieves the state of a specific philosopher.
 * 
 * This function uses a mutex to safely access and retrieve the time of the last
 * meal and the number of meals consumed by a specific philosopher. This prevents
 * data races when multiple threads attempt to read or modify the same data.
 * 
 * @param eat Pointer to an integer where the philosopher's meal count will be stored.
 * @param con Pointer to the `t_cond` structure containing shared program state.
 * @param i Index of the philosopher whose state is being accessed.
 * @return Returns the timestamp of the philosopher's last meal.
 */

long long	get_philo_values(int *eat, t_cond *con, int i)
{
	long long	ml;

	pthread_mutex_lock(con->m_tmeal[i]);
	ml = con->philos[i]->time_last_meal;
	*eat = con->philos[i]->n_times_eats;
	pthread_mutex_unlock(con->m_tmeal[i]);
	return (ml);
}

/**
 * @brief Signals all threads to stop execution safely and simultaneously.
 * 
 * This function iterates through all philosophers and sets their `stop_game` flag
 * to 1, indicating that the simulation should terminate. By using individual flags
 * for each philosopher, it ensures that all threads can terminate simultaneously
 * without contention over a single shared variable. Mutexes are used to guarantee
 * thread safety during updates to the `stop_game` array.
 * 
 * @param con Pointer to the `t_cond` structure containing shared program state.
 */

void	parallel_stop(t_cond *con)
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
/**
 * @brief Evaluates success conditions for the simulation.
 * 
 * This function checks if a philosopher has reached the required number of meals
 * (`hm_eats`). If all philosophers meet this condition, the simulation is stopped
 * by invoking `parallel_stop`. A static counter is used to track the number of
 * philosophers who have achieved success, ensuring thread safety through controlled
 * access to shared state.
 * 
 * @param cond Pointer to the `t_cond` structure containing shared program state.
 * @param i Index of the philosopher being evaluated.
 * @param hm_meals Number of meals consumed by the current philosopher.
 * @return Returns 1 if all success conditions are met, otherwise 0.
 */

char	check_sucess(t_cond *cond, int i, int hm_meals)
{
	static int	count;

	if (cond->hm_eats != -1 && hm_meals >= cond->hm_eats)
	{
		if (!cond->sucess[i])
		{
			cond->sucess[i] = 1;
			count++;
		}
	}
	if (count >= cond->n_philos)
	{
		parallel_stop(cond);
		return (1);
	}
	return (0);
}

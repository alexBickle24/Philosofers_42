/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:24:25 by alejandro         #+#    #+#             */
/*   Updated: 2025/10/27 18:53:10 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Calculates the optimal sleep time for periodic checks.
 * 
 * This function determines the sleep time in microseconds for periodic checks
 * based on the number of philosophers and the frequency per philosopher. It
 * ensures that the sleep time is balanced to avoid excessive CPU usage while
 * maintaining responsiveness in the simulation.
 * 
 * @param num_philos Number of philosophers in the simulation.
 * @param frec_pp Frequency per philosopher in milliseconds.
 * @return The calculated sleep time in microseconds.
 * 
 * @note This function is primarily used in the control thread to regulate
 * periodic checks of philosopher states, such as detecting starvation or
 * success conditions.
 */
long long	usleep_time_controler(int num_philos, int frec_pp)
{
	double		milisec;
	long long	microsec;

	milisec = 1;
	while (1)
	{
		if (milisec * num_philos > frec_pp)
			milisec /= frec_pp;
		else
			break ;
	}
	microsec = milisec * 500;
	return (microsec);
}

/**
 * @brief Calculates a fixed sleep time for working intervals.
 * 
 * This function returns a fixed sleep time in microseconds based on the
 * frequency per philosopher. It is used to control the duration of certain
 * operations in the simulation.
 * 
 * @param frec_pp Frequency per philosopher in milliseconds.
 * @return The calculated sleep time in microseconds.
 * 
 * @note This function is primarily used in the working routines of each
 * philosopher to regulate actions such as eating, sleeping, and thinking.
 */
long long	usleep_time_working(int frec_pp)
{
	long long	microsec;

	microsec = frec_pp * 10;
	return (microsec);
}

/**
 * @brief Retrieves the current timestamp in milliseconds.
 * 
 * This function uses `gettimeofday` to obtain the current time and converts
 * it to milliseconds. It is used to track events such as the time of the last
 * meal or the time of death for a philosopher.
 * 
 * @return The current timestamp in milliseconds.
 * 
 * @note Accurate timestamps are essential for synchronizing events in the
 * simulation and ensuring that time-based conditions are met.
 */
long long	get_timestamp(void)
{
	struct timeval	tv;
	long long		mili_till_day;
	long long		mili_timestamp;

	gettimeofday(&tv, NULL);
	mili_till_day = tv.tv_sec * 1000;
	mili_timestamp = tv.tv_usec / 1000;
	mili_timestamp = mili_till_day + mili_timestamp;
	return (mili_timestamp);
}

/**
 * @brief Checks if the current thread should stop execution.
 * 
 * This function checks the `stop_game` flag for the current philosopher to
 * determine if the thread should terminate. It uses a mutex to ensure thread
 * safety when accessing the shared flag.
 * 
 * @param philo_i Pointer to the philosopher's data structure.
 * @return Returns 1 if the thread should stop, or 0 otherwise.
 * 
 * @note Synchronizing access to the `stop_game` flag prevents data races and
 * ensures that all threads receive consistent information about the simulation
 * state.
 */
char	stop_thread(t_philo *philo_i)
{
	char	ret;

	ret = 0;
	pthread_mutex_lock(philo_i->m_stop);
	if (*(philo_i->stop_game))
		ret = 1;
	pthread_mutex_unlock(philo_i->m_stop);
	return (ret);
}

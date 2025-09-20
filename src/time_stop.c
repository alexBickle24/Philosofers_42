/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:24:25 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/20 00:26:38 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	microsec = milisec * 1000;
	return (microsec);
}

long long	usleep_time_working(int frec_pp)
{
	long long	microsec;

	microsec = frec_pp * 10;
	return (microsec);
}

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

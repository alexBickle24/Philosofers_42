/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:04:16 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/20 01:35:58 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

long long	get_philo_values(int *eat, t_cond *con, int i)
{
	long long	ml;

	pthread_mutex_lock(con->m_tmeal[i]);
	ml = con->philos[i]->time_last_meal;
	*eat = con->philos[i]->n_times_eats;
	pthread_mutex_unlock(con->m_tmeal[i]);
	return (ml);
}

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

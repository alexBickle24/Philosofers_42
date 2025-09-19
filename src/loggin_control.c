/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loggin_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:04:16 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/19 13:42:43 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*control_r(void *arg)
{
	t_conditions	*cond;
	// long long		usleep_t;
	long long		time_last_meal;
	int				hm_meals;
	int				i;
	
	cond = (t_conditions *)arg;
	// usleep_t = usleep_time_controler(cond->n_philos, MS_FREC - 1);
	i = -1;
	while (++i < cond->n_philos)
	{
		pthread_mutex_lock(cond->m_tmeal[i]);
		time_last_meal = cond->philos[i]->time_last_meal;
		hm_meals = cond->philos[i]->n_times_eats;
		pthread_mutex_unlock(cond->m_tmeal[i]);
		if ((get_timestamp() - time_last_meal) >= cond->t_dead)
		{
			cond->dead = get_timestamp();
			parallel_stop(cond);
			return((void *)cond->philos[i]);
		}
		if (check_sucess(cond, i, hm_meals))
			return(NULL);
		if (i == cond->n_philos - 1)
			i = -1;
		usleep(50);//mayor frercuedncia
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

char	check_sucess(t_conditions *cond, int i, int hm_meals)
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
		ft_putstr_fd("sale\n", 2);
		parallel_stop(cond);
		return (1);
	}
	return (0);
}
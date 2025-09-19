/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:42:23 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/19 22:18:06 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	drop_right_fork(t_philo *phi);
char	drop_left_fork(t_philo *phi);
char	take_right_fork(t_philo *phi, long long *start);
char	take_left_fork(t_philo *phi, long long *start);

void	*game_r(void *arg)
{
	t_philo *philo_i;

	philo_i = (t_philo *)arg;
	pthread_mutex_lock(philo_i->m_tmeal);
	philo_i->init_time = get_timestamp();
	philo_i->time_last_meal = get_timestamp();
	pthread_mutex_unlock(philo_i->m_tmeal);
	if (*(philo_i->n_philos) == 1)
	{
		melatonine(philo_i);
		return (NULL);
	}
	if ((philo_i->mphilo_id + 1) % 2 != 0)
		melatonine(philo_i);
	while (!stop_thread(philo_i))
	{
		if (jungle(philo_i)) // intentar comer
			break;
		if (melatonine(philo_i)) // dormir
			break;
	}
	return (NULL);
}

char	melatonine(t_philo *philo)
{
	long long inicio;
	long long time_doing;
	long long usleep_t;

	inicio = get_timestamp();
	philo->timestamp = inicio - philo->init_time;
	if (stop_thread(philo))
		return (1);
	usleep_t = usleep_time_working(1);
	print_philo(philo, philo->mphilo_id, S_SLEEPING, philo->timestamp);
	time_doing = get_timestamp() - inicio;
	while (time_doing <= *(philo->t_sleep))
	{
		if (stop_thread(philo))
			return (1);
		usleep(usleep_t);
		time_doing = get_timestamp() - inicio;
	}
	if (thinking_on_nothing(philo))
		return (1);
	return (0);
}

char	thinking_on_nothing(t_philo *philo)
{
	if (stop_thread(philo))
		return (1);
	philo->timestamp = get_timestamp() - philo->init_time;
	philo->last_state = S_THINKING;
	print_philo(philo, philo->mphilo_id, S_THINKING, philo->timestamp);
	return(0);
}

char jungle(t_philo *philo)
{
	long long	usleep_t;
	long long	start;
	char		ret;

	if (stop_thread(philo))
		return (1);
	usleep_t = usleep_time_working(1);
	if (philo->mphilo_id == *(philo->n_philos) - 1)
	{
		if(!take_right_fork(philo, &start) && !take_left_fork(philo, &start))
		{
			if (stop_thread(philo))
				return (1);
			print_philo(philo, philo->mphilo_id, S_EATING, philo->timestamp);
		}
	}
	else
	{
		if(!take_left_fork(philo, &start) && !take_right_fork(philo, &start))
		{
			if (stop_thread(philo))
				return (1);
			print_philo(philo, philo->mphilo_id, S_EATING, philo->timestamp);
		}
	}
	ret = gains(philo, start, usleep_t);
	if (philo->mphilo_id == *(philo->n_philos) - 1)
	{
		drop_left_fork(philo);
		drop_right_fork(philo);
	}
	else
	{
		drop_right_fork(philo);
		drop_left_fork(philo);
	}
	return (ret);
}


char take_right_fork(t_philo *phi, long long *start)
{
    pthread_mutex_lock(phi->right_fork);

    // Si llegamos aquí, el mutex está bloqueado → el tenedor es nuestro
    if (*(phi->fork_r) == 0) // flag dice que estaba libre
    {
        *start = get_timestamp();
        phi->timestamp = *start - phi->init_time;
        print_philo(phi, phi->mphilo_id, S_TAKING_FORK_RIGHT, phi->timestamp);
        *(phi->fork_r) = 1; // marcarlo ocupado
        return (0); // éxito → mantenemos bloqueado
    }

    // Si la flag dice que estaba ocupado, entonces está desincronizado → lo tratamos como fallo
    pthread_mutex_unlock(phi->right_fork); // liberamos porque realmente no lo usamos
    return (1);
}

char take_left_fork(t_philo *phi, long long *start)
{
    pthread_mutex_lock(phi->left_fork);

    if (*(phi->fork_l) == 0)
    {
        *start = get_timestamp();
        phi->timestamp = *start - phi->init_time;
        print_philo(phi, phi->mphilo_id, S_TAKING_FORK_LEFT, phi->timestamp);
        *(phi->fork_l) = 1;
        return (0);
    }

    pthread_mutex_unlock(phi->left_fork);
    return (1);
}

char drop_right_fork(t_philo *phi)
{
    if (*(phi->fork_r) == 1) // solo si lo teníamos marcado
    {
        *(phi->fork_r) = 0; // liberar flag
        pthread_mutex_unlock(phi->right_fork); // liberar mutex
        return (0);
    }
    return (1);
}

char drop_left_fork(t_philo *phi)
{
    if (*(phi->fork_l) == 1)
    {
        *(phi->fork_l) = 0;
        pthread_mutex_unlock(phi->left_fork);
        return (0);
    }
    return (1);
}

char	gains(t_philo *philo, long long inicio, long long usleep_t)
{
	long long	time_doing;
	
	time_doing = get_timestamp() - inicio;
	while (time_doing <= *(philo->t_eat))
	{
		if (stop_thread(philo))
			return (1);
		usleep(usleep_t);
		time_doing = get_timestamp() - inicio;
	}
	pthread_mutex_lock(philo->m_tmeal);
	philo->time_last_meal = get_timestamp();
	philo->n_times_eats++;
	pthread_mutex_unlock(philo->m_tmeal);
	return (0);
}

void	print_philo(t_philo *philos, int id, int new_state, long long timestamp)
{
	pthread_mutex_lock(philos->m_fd);
	printf("%lld %s%d%s", timestamp, YELLOW, id + 1, RESET);
	if (new_state == S_SLEEPING)
		printf(" %sis sleeping%s %s\n", LIGHT_BLUE, RESET, MOON);
	if (new_state == S_THINKING)
		printf(" %sis thinking%s %s\n", BLUE, RESET, BRAIN);
	if (new_state == S_TAKING_FORK_LEFT) 
		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
	if (new_state == S_TAKING_FORK_RIGHT)
		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
	if (new_state == S_EATING)
		printf(" %sis eating%s %s\n", GREEN, RESET, STEAK);
	pthread_mutex_unlock(philos->m_fd);
}

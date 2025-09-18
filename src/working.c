/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:42:23 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/18 20:56:12 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*game_r(void *arg)
{
	t_philo *philo_i;
	int	iter;

	iter = 1;
	philo_i = (t_philo *)arg;
	philo_i->time_last_meal = get_timestamp();
	if (*(philo_i->n_philos) == 1)
	{
		melatonine(philo_i);
		return (NULL);
	}
	if ((philo_i->mphilo_id + 1) % 2 != 0)
	{
		melatonine(philo_i);
		// if (philo_i->mphilo_id == 1)
		// {
			
		// }
	}
	while (!stop_thread(philo_i))
	{
		if (jungle(philo_i)) // intentar comer
			break;
		if (melatonine(philo_i)) // dormir
			break;
		iter++;
	}
	return (NULL);
}


char	melatonine(t_philo *philo)
{
	long long inicio;
	long long time_doing;
	long long usleep_t;

	if (stop_thread(philo))
		return (1);
	usleep_t = usleep_time_working(MS_FREC);
	pthread_mutex_lock(philo->m_state);
	inicio = get_timestamp();
	philo->timestamp = inicio;
	philo->last_state = S_SLEEPING;
	print_philo(philo, philo->mphilo_id, S_SLEEPING);
	pthread_mutex_unlock(philo->m_state);
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
	pthread_mutex_lock(philo->m_state);
	philo->timestamp = get_timestamp();
	philo->last_state = S_THINKING;
	print_philo(philo, philo->mphilo_id, S_THINKING);
	pthread_mutex_unlock(philo->m_state);
	return(0);
}

// char	jungle(t_philo *philo)
// {
// 	long long	inicio;
// 	long long	usleep_t;

// 	if (stop_thread(philo))
// 		return (1);
// 	usleep_t = usleep_time_working(MS_FREC);
// 	pthread_mutex_lock(philo->left_fork);
// 	pthread_mutex_lock(philo->m_state);
// 	philo->timestamp = get_timestamp();
// 	philo->last_state = S_TAKING_FORK_LEFT;
// 	print_philo(philo, philo->mphilo_id, S_TAKING_FORK_LEFT);
// 	pthread_mutex_unlock(philo->m_state);
// 	pthread_mutex_lock(philo->right_fork);
// 	inicio = get_timestamp();
// 	pthread_mutex_lock(philo->m_state);
// 	philo->timestamp = inicio;
// 	philo->last_state = S_EATING;
// 	print_philo(philo, philo->mphilo_id, S_EATING);
// 	pthread_mutex_unlock(philo->m_state);
// 	if (!gains(philo, inicio, usleep_t))
// 		return (0);
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// 	return (1);
// }

char jungle(t_philo *philo)
{
    long long inicio;
    long long usleep_t;

    if (stop_thread(philo))
        return (1);
    usleep_t = usleep_time_working(MS_FREC);

    // Toma de tenedores
    if (philo->mphilo_id == *(philo->n_philos) - 1)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->m_state);
        philo->timestamp = get_timestamp();
        philo->last_state = S_TAKING_FORK_LEFT; // opcional, podrías crear S_TAKING_FORK_RIGHT
        print_philo(philo, philo->mphilo_id, S_TAKING_FORK_RIGHT);
        print_philo(philo, philo->mphilo_id, S_TAKING_FORK_LEFT);
        pthread_mutex_unlock(philo->m_state);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->m_state);
        philo->timestamp = get_timestamp();
        philo->last_state = S_TAKING_FORK_LEFT;
        print_philo(philo, philo->mphilo_id, S_TAKING_FORK_LEFT);
        print_philo(philo, philo->mphilo_id, S_TAKING_FORK_RIGHT);
        pthread_mutex_unlock(philo->m_state);
    }

    // Comer
    inicio = get_timestamp();
    pthread_mutex_lock(philo->m_state);
    philo->timestamp = inicio;
    philo->last_state = S_EATING;
    print_philo(philo, philo->mphilo_id, S_EATING);
    pthread_mutex_unlock(philo->m_state);

    if (!gains(philo, inicio, usleep_t))
    {
        // Liberar tenedores en orden inverso
        if (philo->mphilo_id == *(philo->n_philos) - 1)
        {
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
        }
        else
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
        }
        return 0;
    }

    return 1;
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
	pthread_mutex_unlock(philo->m_tmeal);
	philo->time_last_meal = get_timestamp();
	pthread_mutex_lock(philo->m_tmeal);
	return (0);
}

void	print_philo(t_philo *philos, int id, int new_state)
{
	pthread_mutex_lock(philos->m_fd);
	printf("%lld %s%d%s", philos->timestamp, YELLOW, id + 1, RESET);
	if (new_state == S_SLEEPING)
		printf(" %sis sleeping%s %s\n", LIGHT_BLUE, RESET, MOON);
	if (new_state == S_THINKING)
		printf(" %sis thinking%s %s\n", BLUE, RESET, BRAIN);
	if (new_state == S_TAKING_FORK_LEFT) 
		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
	if (new_state == S_TAKING_FORK_RIGHT)
		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
	if (new_state == S_EATING)
	{
		printf(" %shas taken a fork%s %s\n", GRAY, RESET, FORK);
		printf("%lld %s%d%s", philos->timestamp, YELLOW, id + 1, RESET);
		printf(" %sis esting%s %s\n", GREEN, RESET, STEAK);
	}
	pthread_mutex_unlock(philos->m_fd);
}
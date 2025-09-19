/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:02:32 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/19 17:11:01 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_all_philos_eats(t_conditions *conditions)
{
    if (!conditions || !conditions->philos)
    {
        printf("Error: Invalid philosopher data.\n");
        return;
    }
    for (int i = 0; i < conditions->n_philos; i++)
    {
        t_philo *philo = conditions->philos[i];
        if (philo)
        {
            printf("Philosopher %d has eaten %d times.\n", philo->mphilo_id, philo->n_times_eats);
        }
        else
        {
            printf("Error: Philosopher %d data is NULL.\n", i + 1);
        }
    }
}


void	print_all_philos_last_meal(t_conditions *conditions)
{
    if (!conditions || !conditions->philos)
    {
        printf("Error: Invalid philosopher data.\n");
        return;
    }
    for (int i = 0; i < conditions->n_philos; i++)
    {
        t_philo *philo = conditions->philos[i];
        if (philo)
        {
            printf("Philosopher %d last_ meal %lld t.\n", philo->mphilo_id, philo->time_last_meal - philo->init_time);
        }
        else
        {
            printf("Error: Philosopher %d data is NULL.\n", i + 1);
        }
    }
}

void	print_all_philos_fields(t_conditions *conditions)
{
    if (!conditions || !conditions->philos)
    {
        printf("Error: Invalid philosopher data.\n");
        return;
    }
    for (int i = 0; i < conditions->n_philos; i++)
    {
        t_philo *philo = conditions->philos[i];
        if (philo)
        {
            printf("Philosopher %d:\n", philo->mphilo_id);
            printf("  Time to eat: %lld\n", *(philo->t_eat));
            printf("  Time to sleep: %lld\n", *(philo->t_sleep));
            printf("  Number of philosophers: %d\n", *(philo->n_philos));
            printf("  Time since last meal: %lld\n", philo->time_last_meal);
            printf("  Number of times eaten: %d\n", philo->n_times_eats);
            printf("  Timestamp: %lld\n", philo->timestamp);
            printf("  Last state: %d\n", philo->last_state);
            printf("  Stop game: %d\n", *(philo->stop_game));
            printf("  Init time: %lld\n", philo->init_time);
            printf("  Mutexes:\n");
            printf("    Right fork: %p\n", (void *)philo->right_fork);
            printf("    Left fork: %p\n", (void *)philo->left_fork);
            printf("    Mutex FD: %p\n", (void *)philo->m_fd);
            printf("    Mutex time meal: %p\n", (void *)philo->m_tmeal);
            printf("    Mutex stop: %p\n", (void *)philo->m_stop);
        }
        else
        {
            printf("Error: Philosopher %d data is NULL.\n", i + 1);
        }
    }
}
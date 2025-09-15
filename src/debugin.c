/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:02:32 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/15 14:17:00 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void print_conditions(t_conditions *conditions)
{
    if (!conditions)
    {
        printf("Error: conditions is NULL\n");
        return;
    }
    printf("=== Program Conditions ===\n");
    printf("Number of Philosophers: %d\n", conditions->n_philos);
    printf("Time to Die: %d ms\n", conditions->t_dead);
    printf("Time to Think: %d ms\n", conditions->t_think);
    printf("Time to Sleep: %d ms\n", conditions->t_sleep);
    printf("Time to Eat: %d ms\n", conditions->t_eat);
    printf("Number of Meals (if specified): %d\n", conditions->hm_eats);
    printf("Stop Game: %d\n", conditions->stop_game);

    // Print Forks Mutexes
    if (conditions->m_forks)
    {
        printf("Fork Mutexes:\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            printf("  Fork %d Mutex: %p\n", i + 1, (void *)conditions->m_forks[i]);
        }
    }
    else
    {
        printf("Fork Mutexes: NULL\n");
    }

    // Print Philosopher Data
    if (conditions->philos)
    {
        printf("=== Philosopher Data ===\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            t_philo *philo = conditions->philos[i];
            if (philo)
            {
                printf("Philosopher %d:\n", i + 1);
                printf("  ID: %d\n", philo->mphilo_id);
                printf("  Last Meal: %d\n", philo->last_meal);
                printf("  Number of Times Eaten: %d\n", philo->n_times_eats);
                printf("  Last State: %d\n", philo->last_state);
                printf("  Left Fork Mutex: %p\n", (void *)philo->left_fork);
                printf("  Right Fork Mutex: %p\n", (void *)philo->right_fork);
                printf("  State Mutex: %p\n", (void *)philo->m_state);
                printf("  Last Meal Mutex: %p\n", (void *)philo->m_tmeal);
                printf("  Stop Mutex: %p\n", (void *)philo->m_stop);
            }
            else
            {
                printf("Philosopher %d: NULL\n", i + 1);
            }
        }
    }
    else
    {
        printf("Philosopher Data: NULL\n");
    }

    // Print Threads
    if (conditions->threads)
    {
        printf("=== Threads ===\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            if (conditions->threads[i])
                printf("  Philosopher %d Thread: %p\n", i + 1, (void *)conditions->threads[i]);
            else
                printf("  Philosopher %d Thread: NULL\n", i + 1);
        }
    }
    else
    {
        printf("Threads: NULL\n");
    }

    // Print Logging and Control Threads
    printf("Logging Thread: %p\n", (void *)conditions->loggin_thread);
    printf("Start/End Thread: %p\n", (void *)conditions->start_end_thread);

    // Print State Mutexes
    if (conditions->m_state)
    {
        printf("State Mutexes:\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            printf("  State Mutex %d: %p\n", i + 1, (void *)conditions->m_state[i]);
        }
    }
    else
    {
        printf("State Mutexes: NULL\n");
    }

    // Print Last Meal Mutexes
    if (conditions->m_tmeal)
    {
        printf("Last Meal Mutexes:\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            printf("  Last Meal Mutex %d: %p\n", i + 1, (void *)conditions->m_tmeal[i]);
        }
    }
    else
    {
        printf("Last Meal Mutexes: NULL\n");
    }

    // Print Stop Mutex
    printf("Stop Mutex: %p\n", (void *)conditions->m_stop);
}

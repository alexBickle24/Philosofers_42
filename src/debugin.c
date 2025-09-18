/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:02:32 by alejandro         #+#    #+#             */
/*   Updated: 2025/09/18 16:40:19 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#include "../inc/philo.h"

void print_conditions(t_conditions *conditions)
{
    if (!conditions)
    {
        printf("\033[1;31mError: conditions is NULL\033[0m\n");
        return;
    }

    printf("\033[1;34m=== Program Conditions ===\033[0m\n");
    printf("\033[1;32mNumber of Philosophers:\033[0m %d\n", conditions->n_philos);
    printf("\033[1;32mTime to Die:\033[0m %lld ms\n", conditions->t_dead);
    printf("\033[1;32mTime to Sleep:\033[0m %lld ms 🌙\n", conditions->t_sleep);
    printf("\033[1;32mTime to Eat:\033[0m %lld ms\n", conditions->t_eat);
    printf("\033[1;32mNumber of Meals (if specified):\033[0m %d\n", conditions->hm_eats);
    printf("\033[1;32mStop Game:\033[0m %d\n", *conditions->stop_game);

    // Print Forks Mutexes
    if (conditions->m_forks)
    {
        printf("\033[1;34mFork Mutexes:\033[0m\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            printf("  🍴 Fork %d Mutex: %p\n", i + 1, (void *)conditions->m_forks[i]);
        }
    }
    else
    {
        printf("\033[1;31mFork Mutexes: NULL\033[0m\n");
    }

    // Print Philosopher Data
    if (conditions->philos)
    {
        printf("\033[1;34m=== Philosopher Data ===\033[0m\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            t_philo *philo = conditions->philos[i];
            if (philo)
            {
                printf("\033[1;33mPhilosopher %d:\033[0m\n", i + 1);
                printf("  ID: %d\n", philo->mphilo_id);
                printf("  Last Meal: %lld ms\n", philo->time_last_meal);
                printf("  Number of Times Eaten: %d\n", philo->n_times_eats);
                printf("  Last State: %d\n", philo->last_state);
                printf("  🍴 Left Fork Mutex: %p\n", (void *)philo->left_fork);
                printf("  🍴 Right Fork Mutex: %p\n", (void *)philo->right_fork);
                printf("  State Mutex: %p\n", (void *)philo->m_state);
                printf("  Last Meal Mutex: %p\n", (void *)philo->m_tmeal);
                printf("  Stop Mutex: %p\n", (void *)philo->m_stop);
            }
            else
            {
                printf("\033[1;31mPhilosopher %d: NULL\033[0m\n", i + 1);
            }
        }
    }
    else
    {
        printf("\033[1;31mPhilosopher Data: NULL\033[0m\n");
    }

    // Print Threads
    if (conditions->threads)
    {
        printf("\033[1;34m=== Threads ===\033[0m\n");
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
        printf("\033[1;31mThreads: NULL\033[0m\n");
    }

    // Print Logging and Control Threads
    printf("\033[1;34mLogging Thread:\033[0m %p\n", (void *)conditions->loggin_thread);
    printf("\033[1;34mStart/End Thread:\033[0m %p\n", (void *)conditions->start_end_thread);

    // Print State Mutexes
    if (conditions->m_state)
    {
        printf("\033[1;34mState Mutexes:\033[0m\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            printf("  State Mutex %d: %p\n", i + 1, (void *)conditions->m_state[i]);
        }
    }
    else
    {
        printf("\033[1;31mState Mutexes: NULL\033[0m\n");
    }

    // Print Last Meal Mutexes
    if (conditions->m_tmeal)
    {
        printf("\033[1;34mLast Meal Mutexes:\033[0m\n");
        for (int i = 0; i < conditions->n_philos; i++)
        {
            printf("  Last Meal Mutex %d: %p\n", i + 1, (void *)conditions->m_tmeal[i]);
        }
    }
    else
    {
        printf("\033[1;31mLast Meal Mutexes: NULL\033[0m\n");
    }

    // Print Stop Mutex
    printf("\033[1;34mStop Mutex:\033[0m %p\n", (void *)conditions->m_stop);
}
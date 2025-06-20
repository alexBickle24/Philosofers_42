/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:29:14 by alex              #+#    #+#             */
/*   Updated: 2025/06/20 13:22:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "libft.h"
#include <sys/time.h>
#include <pthread.h>

typedef struct philo_data
{
    int mphilo_id;
    struct timeval tv;
}      philo;

typedef struct program_conditions
{
    int n_philos;
    int t_dead;
    int t_think;
    int t_sleep;
    int t_eat;
	int hm_eats;
    int *forks;
    int *is_dead;
    char stop_program;
	philo *philos;
}       p_conditions;

int	fill_data(p_conditions* philo_data, char **p_data);

#endif




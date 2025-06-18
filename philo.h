




#ifndef PHILO_H
# define PHILO_H


#include <pthreads.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"


typedef struct control_thread
{
    
}           c_thread;

typedef struct philo_data
{
    int philo_id;
    struct timeval tv;
}      philo;

typedef struct program_data
{
    int n_philos;
    int t_dead;
    int t_think:
    int t_sleep;
    int t_eat;
    int *forks;
    int *is_dead;
    char stop_program;
    char 

}       p_data;


#endif
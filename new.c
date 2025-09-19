

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
		if(!drop_left_fork(philo) && !drop_right_fork(philo))
		{
			pthread_mutex_lock(philo->m_tmeal);
			philo->time_last_meal = get_timestamp();
			philo->n_times_eats++;
			pthread_mutex_unlock(philo->m_tmeal);
		}
	}
	else
	{
		if(!drop_right_fork(philo) && !drop_left_fork(philo))
		{
			pthread_mutex_lock(philo->m_tmeal);
			philo->time_last_meal = get_timestamp();
			philo->n_times_eats++;
			pthread_mutex_unlock(philo->m_tmeal);
		}
	}
	return (ret);
}

char	take_right_fork(t_philo *phi, long long *start)
{
	pthread_mutex_lock(phi->right_fork);
	if (!*(phi->fork_r))
	{
		*start = get_timestamp();
		phi->timestamp = *start - phi->init_time;
		print_philo(phi, phi->mphilo_id, S_TAKING_FORK_RIGHT, phi->timestamp);
		*(phi->fork_r) = 1;
		return (0);
	}
	return (1);
}

char	take_left_fork(t_philo *phi, long long *start)
{
	pthread_mutex_lock(phi->left_fork);
	if (!*(phi->fork_l))
	{
		*start = get_timestamp();
		phi->timestamp = *start - phi->init_time;
		print_philo(phi, phi->mphilo_id, S_TAKING_FORK_LEFT, phi->timestamp);
		*(phi->fork_l) = 1;
		return (0);
	}
	return (1);
}

char	drop_left_fork(t_philo *phi)
{
	if (*(phi->fork_l))
	{
		*(phi->fork_l) = 0;
		pthread_mutex_unlock(phi->left_fork);
		return (0);
	}
	return (1);
}

char	drop_right_fork(t_philo *phi)
{
	if (*(phi->fork_r))
	{
		*(phi->fork_r) = 0;
		pthread_mutex_unlock(phi->right_fork);
		return (0);
	}
	return (1);
}




char jungle(t_philo *philo)
{
    long long inicio;
    long long usleep_t;
	char ret;

    if (stop_thread(philo))
        return (1);
    usleep_t = usleep_time_working(1);

    // Toma de tenedores
    if (philo->mphilo_id == *(philo->n_philos) - 1 /*&& *(philo->n_philos) != 2*/)
    {
		
        // pthread_mutex_lock(philo->right_fork);
        // pthread_mutex_lock(philo->left_fork);
		// inicio = get_timestamp();
		// philo->timestamp = inicio - philo->init_time;
        // print_philo(philo, philo->mphilo_id, S_TAKING_FORK_RIGHT, philo->timestamp);
        // print_philo(philo, philo->mphilo_id, S_TAKING_FORK_LEFT, philo->timestamp);
    }
    else
    {
        // pthread_mutex_lock(philo->left_fork);
        // pthread_mutex_lock(philo->right_fork);
        // inicio = get_timestamp();
		// philo->timestamp = inicio - philo->init_time;
        // print_philo(philo, philo->mphilo_id, S_TAKING_FORK_LEFT, philo->timestamp);
        // print_philo(philo, philo->mphilo_id, S_TAKING_FORK_RIGHT, philo->timestamp);
    }

    if (stop_thread(philo))
        return (1);
    philo->last_state = S_EATING;
    print_philo(philo, philo->mphilo_id, S_EATING, philo->timestamp);
	ret = gains(philo, inicio, usleep_t);
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
	return (ret);
}
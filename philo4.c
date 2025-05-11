/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:29:29 by jainavas          #+#    #+#             */
/*   Updated: 2025/05/11 20:50:22 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Improved sleep function that checks for simulation events
 * 
 * Sleeps for the specified time while periodically checking if the
 * philosopher has starved or if the simulation has ended.
 * 
 * @param mstosleep Time to sleep in milliseconds
 * @param philo Philosopher who is sleeping
 * @return 1 if simulation should end, 0 otherwise
 */
int	bettersleep(long mstosleep, t_philo *philo)
{
	long			start;
	long			curr;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	curr = start;
	while (curr - start < mstosleep)
	{
		usleep(9);
		if ((timeinms(&tv, philo) - philo->f) > philo->timetodiems)
			return (philo->dead = 1, putsimovr(philo), 1);
		if (checksim(philo))
			return (1);
		gettimeofday(&tv, NULL);
		curr = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	return (0);
}

/**
 * @brief Sets the simulation's "over" flag in a thread-safe way
 * 
 * Used when a philosopher dies to signal all threads to terminate.
 * 
 * @param philo Philosopher with access to simulation control
 */
void	putsimovr(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->lock);
	philo->sim->sim_over = 1;
	pthread_mutex_unlock(&philo->sim->lock);
}

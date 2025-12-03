/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:53:18 by jainavas          #+#    #+#             */
/*   Updated: 2024/11/07 10:53:18 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Sleeps for the specified duration in milliseconds
 * 
 * Uses busy-waiting with small usleep intervals for precise timing.
 * 
 * @param ms Duration to sleep in milliseconds
 */
void	ft_usleep(long ms)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}

/**
 * @brief Gets the current time in milliseconds
 * 
 * Uses gettimeofday to get current timestamp and converts to milliseconds.
 * 
 * @return Current time in milliseconds since epoch
 */
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 * @brief Cleans up all allocated resources
 * 
 * Closes and unlinks all semaphores, frees the pids array.
 * 
 * @param data Pointer to the simulation data structure
 */
void	cleanup(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->death);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	free(data->pids);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:29:29 by jainavas          #+#    #+#             */
/*   Updated: 2024/12/10 01:20:18 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	putsimovr(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->lock);
	philo->sim->sim_over = 1;
	pthread_mutex_unlock(&philo->sim->lock);
}

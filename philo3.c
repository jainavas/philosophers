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

long int	timeinms(struct timeval *tv, int x, int c)
{
	gettimeofday(tv, NULL);
	return (((tv->tv_usec - x) / 1000 + (tv->tv_sec - c) * 1000));
}

int	checksim(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->lock);
	if (philo->sim->sim_over)
	{
		pthread_mutex_unlock(&philo->sim->lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->sim->lock);
		return (0);
	}
}

int	routinewhile(t_philo *philo, struct timeval *tv, t_timec *time)
{
	while (1)
	{
		time->f = timeinms(tv, time->x, time->c);
		printf("%ld %d is thinking\n", timeinms(tv, time->x, time->c),
			philo->philonum);
		eat(philo, tv, time->x, time->c);
		if ((timeinms(tv, time->x, time->c) - time->f) > philo->timetodiems
			|| checksim(philo))
			break ;
		printf("%ld %d is sleeping\n", timeinms(tv, time->x, time->c),
			philo->philonum);
		usleep(philo->timetosleepms * 1000);
		if ((timeinms(tv, time->x, time->c) - time->f) > philo->timetodiems
			|| checksim(philo))
			break ;
	}
	return (0);
}

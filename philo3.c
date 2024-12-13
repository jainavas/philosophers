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

long int	timeinms(struct timeval *tv, t_philo *philo)
{
	long int	tmp;

	gettimeofday(tv, NULL);
	pthread_mutex_lock(&philo->time->lock);
	tmp = ((tv->tv_usec - philo->time->x) / 1000
			+ (tv->tv_sec - philo->time->c) * 1000);
	pthread_mutex_unlock(&philo->time->lock);
	return (tmp);
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

int	routinewhile(t_philo *philo, struct timeval *tv)
{
	philo->f = timeinms(tv, philo);
	while (1)
	{
		if (eat(philo, tv))
			return (1);
		if (checksim(philo))
			return (1);
		if ((timeinms(tv, philo) - philo->f) > philo->timetodiems)
			return (philo->dead = 1, putsimovr(philo), 1);
		printf("%ld %d is sleeping\n", timeinms(tv, philo), philo->philonum);
		if (bettersleep(philo->timetosleepms, philo))
			return (1);
		printf("%ld %d is thinking\n", timeinms(tv, philo), philo->philonum);
		usleep(200);
	}
	return (0);
}

int	getforkeven(t_philo *philo, struct timeval *tv)
{
	usleep(200);
	pthread_mutex_lock(&philo->right->lock);
	if (checksim(philo))
		return (pthread_mutex_unlock(&philo->right->lock), 1);
	printf("%ld %d has taken a fork\n", timeinms(tv, philo), philo->philonum);
	if ((timeinms(tv, philo) - philo->f) > philo->timetodiems)
		return (pthread_mutex_unlock(&philo->right->lock), philo->dead = 1, 1);
	pthread_mutex_lock(&philo->lock);
	if (checksim(philo))
		return (pthread_mutex_unlock(&philo->lock),
			pthread_mutex_unlock(&philo->right->lock), 1);
	printf("%ld %d has taken a fork\n", timeinms(tv, philo), philo->philonum);
	return (0);
}

int	getforkodd(t_philo *philo, struct timeval *tv)
{
	pthread_mutex_lock(&philo->lock);
	if (checksim(philo))
		return (pthread_mutex_unlock(&philo->lock), 1);
	printf("%ld %d has taken a fork\n", timeinms(tv, philo), philo->philonum);
	if (philo->philosall == 1)
		return (usleep(philo->timetodiems * 1000),
			pthread_mutex_unlock(&philo->lock), philo->dead = 1, 1);
	if ((timeinms(tv, philo) - philo->f) > philo->timetodiems)
		return (pthread_mutex_unlock(&philo->lock), philo->dead = 1, 1);
	pthread_mutex_lock(&philo->right->lock);
	if (checksim(philo))
		return (pthread_mutex_unlock(&philo->lock),
			pthread_mutex_unlock(&philo->right->lock), 1);
	gettimeofday(tv, NULL);
	printf("%ld %d has taken a fork\n", timeinms(tv, philo), philo->philonum);
	return (0);
}

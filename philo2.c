/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:40:23 by jainavas          #+#    #+#             */
/*   Updated: 2024/11/04 21:40:23 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philonew(t_philo **philos, int num)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->fork = 1;
	if (!*philos)
	{
		new->left = NULL;
		*philos = new;
	}
	else
	{
		new->left = philolast(*philos);
		new->left->right = new;
	}
	new->philonum = num;
	new->right = NULL;
	pthread_mutex_init(&new->lock, NULL);
}

void	freephilos(t_philo **philos, int nphilos)
{
	t_philo	*tmp;

	while (nphilos-- > 0)
	{
		tmp = (*philos)->right;
		pthread_mutex_destroy(&(*philos)->lock);
		free(*philos);
		*philos = tmp;
	}
}

t_philo	*philolast(t_philo *lst)
{
	t_philo	*tmp;

	tmp = lst;
	if (tmp)
		while (tmp->right)
			tmp = tmp->right;
	return (tmp);
}

void	eat(t_philo *philo, struct timeval *tv)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->right->lock);
	gettimeofday(tv, NULL);
	printf("%ld %d has taken a fork\n", tv->tv_usec / 1000, philo->philonum);
	usleep(philo->timetoeatms * 1000);
	gettimeofday(tv, NULL);
	printf("%ld %d is eating\n", (tv->tv_usec) / 1000, philo->philonum);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->right->lock);
}

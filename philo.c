/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:45:18 by jainavas          #+#    #+#             */
/*   Updated: 2024/11/03 22:12:52 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freephilos(t_philo **philos, int nphilos)
{
	t_philo *tmp;

	while (nphilos-- > 0)
	{
		tmp = (*philos)->right;
		pthread_mutex_destroy(&(*philos)->lock);
		free(*philos);
		*philos = tmp;
	}
}

void	philonew(t_philo **philos, int num)
{
	t_philo	*new;
	struct timeval	tv;

	new = malloc(sizeof(t_philo));
	new->fork = 1;
	gettimeofday(&tv, NULL);
	new->alltime = tv.tv_usec;
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

void	philoinit(t_philo *philo, char **argv)
{
	philo->timetodiems = ft_atoi(argv[2]);
	philo->timetoeatms = ft_atoi(argv[3]);
	philo->timetosleepms = ft_atoi(argv[4]);
	philo->maxtimeseaten = ft_atoi(argv[5]);
	pthread_create(&philo->thread, NULL, philo_routine, philo);
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

void	makeround(int nphilos, t_philo **philos, char **argv)
{
	t_philo	*tmp;
	int		n;
	
	tmp = *philos;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = *philos;
	(*philos)->left = tmp;
	tmp = *philos;
	n = 0;
	while (nphilos > n++)
	{
		philoinit(tmp, argv);
		tmp = tmp->right;
	}
	n = 0;
	while (nphilos > n++)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->right;
	}
}

void	*philo_routine(t_philo *philo)
{
	struct timeval	tv;
	int				x;
	int				c;

	gettimeofday(&tv, NULL);
	x = tv.tv_usec;
	c = 0;
	while (philo->timetodiems > (tv.tv_usec - x) / 1000
		&& c < philo->maxtimeseaten)
	{
		x = tv.tv_usec;
		printf("%ld %d is thinking\n",(tv.tv_usec)/1000, philo->philonum);
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->right->lock);
		printf("%ld %d has taken a fork\n",(tv.tv_usec)/1000, philo->philonum);
		usleep(philo->timetoeatms * 1000);
		gettimeofday(&tv, NULL);
		printf("%ld %d is eating\n",(tv.tv_usec)/1000, philo->philonum);
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->right->lock);
		printf("%ld %d is sleeping\n",(tv.tv_usec)/1000, philo->philonum);
		usleep(philo->timetosleepms * 1000);
		gettimeofday(&tv, NULL);
		c++;
	}
	printf("%ld %d died\n",(tv.tv_usec)/1000, philo->philonum);
}

int main(int argc, char **argv)
{
	t_philo			*philos;
	t_philo			*tmp;
	int				x;
	int				numphilos;

	x = 0;
	philos = NULL;
	numphilos = ft_atoi(argv[1]);
	while (x++ < numphilos)
		philonew(&philos, x);
	makeround(numphilos, &philos, argv);
	freephilos(&philos, numphilos);
}
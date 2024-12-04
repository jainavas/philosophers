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

void	philonew(t_philo **philos, int num, int numphilos)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->philosall = numphilos;
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
	new->dead = 0;
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

int	eat(t_philo *philo, struct timeval *tv)
{
	if (philo->philonum % 2 == 0)
		if (getforkeven(philo, tv))
			return (1);
	if (philo->philonum % 2 == 1)
		if (getforkodd(philo, tv))
			return (1);
	gettimeofday(tv, NULL);
	printf("%ld %d is eating\n", timeinms(tv, philo),
		philo->philonum);
	usleep(philo->timetoeatms * 1000);
	philo->f = timeinms(tv, philo);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->right->lock);
	philo->maxtimeseaten--;
	if (philo->maxtimeseaten == 0)
	{
		pthread_mutex_lock(&philo->sim->lock);
		philo->sim->sim_over = 1;
		pthread_mutex_unlock(&philo->sim->lock);
	}
	return (0);
}

int	inputdebug(int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || checkoverflow(argv[1]) == -1
		|| checkoverflow(argv[2]) == -1 || checkoverflow(argv[3]) == -1
		|| checkoverflow(argv[4]) == -1)
		return (printf("Argumentos mal\n"), -1);
	if (argc == 6 && (checkoverflow(argv[5]) == -1 || ft_atoi(argv[5]) < 0))
		return (printf("Argumentos mal\n"), -1);
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (printf("Argumentos negativos\n"), -1);
	return (0);
}

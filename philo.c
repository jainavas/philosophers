/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:45:18 by jainavas          #+#    #+#             */
/*   Updated: 2024/11/06 20:42:34 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philoinit(t_philo *philo, char **argv)
{
	philo->timetodiems = ft_atoi(argv[2]);
	philo->timetoeatms = ft_atoi(argv[3]);
	philo->timetosleepms = ft_atoi(argv[4]);
	if (argv[5])
		philo->maxtimeseaten = ft_atoi(argv[5]);
	else
		philo->maxtimeseaten = INT_MAX;
	pthread_create(&philo->thread, NULL, philo_routine, (void *)philo);
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

void	*philo_routine(void *philovoid)
{
	t_philo			*philo;
	struct timeval	tv;
	int				x;
	int				c;
	int				f;

	gettimeofday(&tv, NULL);
	philo = (t_philo *)philovoid;
	x = tv.tv_usec;
	c = tv.tv_sec;
	while (1)
	{
		gettimeofday(&tv, NULL);
		f = ((tv.tv_usec - x) / 1000 + (tv.tv_sec - c) * 1000);
		printf("%ld %d is thinking\n",((tv.tv_usec - x) / 1000 + (tv.tv_sec - c) * 1000), philo->philonum);
		eat(philo, &tv, x, c);
		if ((((tv.tv_usec - x) / 1000 + (tv.tv_sec - c) * 1000) - f) > philo->timetodiems)
			break;
		printf("%ld %d is sleeping\n", ((tv.tv_usec - x) / 1000 + (tv.tv_sec - c) * 1000), philo->philonum);
		usleep(philo->timetosleepms * 1000);
		gettimeofday(&tv, NULL);
		if ((((tv.tv_usec - x) / 1000 + (tv.tv_sec - c) * 1000) - f) > philo->timetodiems)
			break;
	}
	printf("%ld %d died\n", ((tv.tv_usec - x) / 1000 + (tv.tv_sec - c) * 1000), philo->philonum);
	freephilos(&philo, philo->philosall);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	int				x;
	int				numphilos;

	x = 0;
	philos = NULL;
	if (inputdebug(argc, argv) == -1)
		return (-1);
	numphilos = ft_atoi(argv[1]);
	while (x++ < numphilos)
		philonew(&philos, x, numphilos);
	makeround(numphilos, &philos, argv);
	freephilos(&philos, numphilos);
}

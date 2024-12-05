/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:45:18 by jainavas          #+#    #+#             */
/*   Updated: 2024/12/05 18:14:19 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philoinit(t_philo *philo, char **argv, t_sim *control)
{
	philo->timetodiems = ft_atoi(argv[2]);
	philo->timetoeatms = ft_atoi(argv[3]);
	philo->timetosleepms = ft_atoi(argv[4]);
	if (argv[5])
		philo->maxtimeseaten = ft_atoi(argv[5]);
	else
		philo->maxtimeseaten = INT_MAX;
	philo->sim = control;
	pthread_create(&philo->thread, NULL, philo_routine, (void *)philo);
}

void	makeround(int nphilo, t_philo **philos, char **argv, t_sim *control)
{
	t_philo	*tmp;
	t_timec	time;
	int		n;

	tmp = *philos;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = *philos;
	(*philos)->left = tmp;
	tmp = *philos;
	n = 0;
	pthread_mutex_init(&time.lock, NULL);
	while (nphilo > n++)
	{
		tmp->time = &time;
		philoinit(tmp, argv, control);
		tmp = tmp->right;
	}
	n = 0;
	while (nphilo > n++)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->right;
	}
}

void	*philo_routine(void *philovoid)
{
	t_philo			*philo;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo = (t_philo *)philovoid;
	pthread_mutex_lock(&philo->time->lock);
	philo->time->x = tv.tv_usec;
	philo->time->c = tv.tv_sec;
	pthread_mutex_unlock(&philo->time->lock);
	routinewhile(philo, &tv);
	pthread_mutex_lock(&philo->sim->lock);
	philo->sim->sim_over = 1;
	pthread_mutex_unlock(&philo->sim->lock);
	if (philo->dead == 1)
	{
		pthread_mutex_lock(&philo->sim->lock);
		if (philo->sim->dontprint == 0)
			printf("%ld %d died\n", timeinms(&tv, philo), philo->philonum);
		philo->sim->dontprint = 1;
		pthread_mutex_unlock(&philo->sim->lock);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	int				x;
	int				numphilos;
	t_sim			control;

	x = 0;
	philos = NULL;
	control.sim_over = 0;
	control.dontprint = 0;
	pthread_mutex_init(&control.lock, NULL);
	if (inputdebug(argc, argv) == -1)
		return (-1);
	numphilos = ft_atoi(argv[1]);
	while (x++ < numphilos)
		philonew(&philos, x, numphilos);
	makeround(numphilos, &philos, argv, &control);
	freephilos(&philos, numphilos);
}

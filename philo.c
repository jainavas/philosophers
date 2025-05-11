/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:45:18 by jainavas          #+#    #+#             */
/*   Updated: 2025/05/11 20:49:56 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes a philosopher with the simulation parameters
 * 
 * Sets up timing values, maximum eat count, and creates a thread for the
 * philosopher to run its routine.
 * 
 * @param philo The philosopher structure to initialize
 * @param argv Command line arguments containing simulation parameters
 * @param control Shared control structure for the simulation
 */
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

/**
 * @brief Creates a circular linked list of philosophers and runs the simulation
 * 
 * Connects all philosophers in a circular list, initializes them with a shared
 * time structure, starts their threads and waits for all threads to finish.
 * 
 * @param nphilo Number of philosophers in the simulation
 * @param philos Pointer to the first philosopher in the list
 * @param argv Command line arguments containing simulation parameters
 * @param control Shared control structure for the simulation
 */
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

/**
 * @brief The main routine each philosopher thread executes
 * 
 * Handles the philosopher's lifecycle of eating, sleeping, and thinking.
 * Monitors for starvation and terminates when the philosopher dies or
 * the simulation ends.
 * 
 * @param philovoid Void pointer to the philosopher structure (cast to t_philo)
 * @return NULL when the thread completes
 */
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

/**
 * @brief Main entry point for the philosophers simulation
 * 
 * Validates input, creates philosopher structures, runs the simulation,
 * and handles cleanup afterward.
 * 
 * @param argc Argument count
 * @param argv Command line arguments
 * @return 0 on success, -1 on error
 */
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

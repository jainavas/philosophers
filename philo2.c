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

/**
 * @brief Creates a new philosopher and adds it to the linked list
 * 
 * Allocates memory for a new philosopher, assigns its number and initializes
 * its mutex. Connects it to the existing list if any.
 * 
 * @param philos Double pointer to the list of philosophers
 * @param num The ID number of this philosopher
 * @param numphilos Total number of philosophers in the simulation
 */
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

/**
 * @brief Frees all allocated memory for philosophers
 * 
 * Destroys mutexes and frees memory for each philosopher structure in the list.
 * 
 * @param philos Double pointer to the list of philosophers
 * @param nphilos Number of philosophers to free
 */
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

/**
 * @brief Finds the last philosopher in the linked list
 * 
 * Traverses the list to find the philosopher with no right neighbor.
 * 
 * @param lst Pointer to any philosopher in the list
 * @return Pointer to the last philosopher in the list
 */
t_philo	*philolast(t_philo *lst)
{
	t_philo	*tmp;

	tmp = lst;
	if (tmp)
		while (tmp->right)
			tmp = tmp->right;
	return (tmp);
}

/**
 * @brief Handles the eating phase of a philosopher
 * 
 * Acquires forks in the correct order based on philosopher number,
 * simulates eating for a specified time, then releases the forks.
 * 
 * @param philo The philosopher who is eating
 * @param tv Timeval structure for timing
 * @return 1 if simulation should end, 0 to continue
 */
int	eat(t_philo *philo, struct timeval *tv)
{
	if (philo->maxtimeseaten == 0)
		return (usleep(philo->timetodiems * 1000), 1);
	if (philo->philonum % 2 == 0)
		if (getforkeven(philo, tv))
			return (1);
	if (philo->philonum % 2 == 1)
		if (getforkodd(philo, tv))
			return (1);
	printf("%ld %d is eating\n", timeinms(tv, philo),
		philo->philonum);
	if (bettersleep(philo->timetoeatms, philo))
		return (pthread_mutex_unlock(&philo->lock),
			pthread_mutex_unlock(&philo->right->lock), 1);
	philo->f = timeinms(tv, philo);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->right->lock);
	philo->maxtimeseaten--;
	return (0);
}

/**
 * @brief Validates command line arguments for the simulation
 * 
 * Checks if the correct number of arguments is provided and
 * that all values are positive and don't overflow.
 * 
 * @param argc Argument count
 * @param argv Command line arguments
 * @return 0 if arguments are valid, -1 otherwise
 */
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
